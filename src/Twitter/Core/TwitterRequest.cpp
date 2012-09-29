#include "TwitterRequest.h"

#include "TwitterSession.h"
#include "Utils.h"
#include "OAuth.h"
#include "Utils/urlencode.h"
#include "TwitterConstants.h"
#include "TwitterRequestListener.h"



TwitterRequest::TwitterRequest( TwitterSession* session, const std::string& url ) 
							  : CurlProcess(url),  _session(session) {

 	pthread_mutex_init(&_data_mutex_rw,NULL);

}

TwitterRequest::~TwitterRequest() {

}




TwitterSession* TwitterRequest::get_session() {
	return _session;
}


std::string TwitterRequest::get_response_data() {

	pthread_mutex_lock( &_data_mutex_rw );

		return _response_data;

	pthread_mutex_unlock( &_data_mutex_rw );

}


void TwitterRequest::_on_data_received( const std::string& data ) {

	Utils::debug("//////////////////////////////\n " + data );

	pthread_mutex_lock( &_data_mutex_rw );

		_response_data += data;

	pthread_mutex_unlock( &_data_mutex_rw );


	this->on_data_received( data );
}

void TwitterRequest::on_data_received( const std::string& data ) {

	if ( !_listeners.empty() ) {

		std::set<TwitterRequestListener*>::iterator iter;
		for ( iter = _listeners.begin(); iter != _listeners.end(); iter++ ) {

			(*iter)->on_request_data_received( this, data );

		}

		return;
	}

	Utils::debug("No listeners !");

}

void TwitterRequest::_on_connection_closed( unsigned long response_code ) {
	Utils::debug("/////////////// C /////////////// --> " + Utils::otos(response_code) );

	this->on_connection_closed(response_code);
}

void TwitterRequest::on_connection_closed( unsigned long response_code ) {

	if ( !_listeners.empty() ) {

		std::set<TwitterRequestListener*>::iterator iter;
		for ( iter = _listeners.begin(); iter != _listeners.end(); iter++ ) {

			(*iter)->on_request_connection_closed( this, response_code );

		}

		return;
	}

	Utils::debug("No listeners !");

}


void TwitterRequest::add_listener( TwitterRequestListener* listener ) {

	_listeners.erase(_session);
	_listeners.insert(listener);

}

void TwitterRequest::remove_listener( TwitterRequestListener* listener ) {
	_listeners.erase(listener);
}


void TwitterRequest::prepare() {

	CurlProcess::prepare();

	const std::string& http_proxy = _session->get_HTTP_proxy();
	if ( http_proxy != DEFAULT_PROXY ) {
		curl_easy_setopt( _curl, CURLOPT_PROXY, http_proxy.c_str() );
	}

    std::string data;

    e_HTTP_request_type method = GET;

    if ( _POST_data.size() > 0 ) {
    	method = POST;
    	data = concatenate_data(_POST_data);
    }
    else {
    	data = concatenate_data(_GET_data);
    }

	std::string oauth_header = _session->get_oauth().get_oauth_header( method, _url, data );
    
	if ( oauth_header.size() > 0 ) {
    	this->set_oauth_header( oauth_header );
    }


    if ( _listeners.empty() ) {
    	_listeners.insert( _session );
    }


}


void TwitterRequest::set_oauth_header( const std::string& header ) {

	if ( header.size() > 0 ) {
		_headerList = curl_slist_append( _headerList, header.c_str() );
	}
	
}

