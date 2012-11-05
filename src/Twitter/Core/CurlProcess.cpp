#include "CurlProcess.h"

#include "Utils.h"
#include "Utils/urlencode.h"

CurlProcess::CurlProcess( const std::string& url ) 
: _thread_id(-1), _url(url), _running(false), _response_code(999), _header_list(NULL), _form_post(NULL), _form_end(NULL)  {

	_curl = this->load_curl();

}



CurlProcess::~CurlProcess() {

	this->stop();
	
	if ( _header_list != NULL ) {
		curl_slist_free_all( _header_list );
	}

    if ( _form_post != NULL ) {
    	curl_formfree(_form_post);
    }

	curl_easy_cleanup( _curl );
    _curl = NULL;

}


CURL* CurlProcess::load_curl() {

	/* Initialize cURL */
    CURL* curl = curl_easy_init();
    if( curl == NULL ) {
        std::string dummyStr;
        Utils::debug("CURL ERROR");
    }
    else {

	    curl_easy_setopt( curl, CURLOPT_ENCODING, "" );

    }

    return curl;

}


size_t _callback_data_bumper( char* ptr, size_t size, size_t nmemb, void* userdata ) {

    std::string data;
    data.assign(ptr);

	
    CurlProcess* me = static_cast<CurlProcess*>(userdata);
    me->_on_data_received( data );

    return size*nmemb;

}


void* start_thread( void* class_ptr ) {

    static_cast<CurlProcess*>(class_ptr)->send( ); 

	return NULL;

}


int CurlProcess::send_async() {

	if ( !_running ) {
		int ret;
		if ( (ret = pthread_create( &_thread_id, NULL, &start_thread, this )) == 0 ) {
			_running = true;
		}
		
		return ret;
	}
	else {
		return -14;
	}

}

int CurlProcess::stop() {

	if ( _running && _thread_id != -1 ) {

		std::cout << "<<< STOPPING >>> thread. ...\n";
		int ret = pthread_cancel( _thread_id );
		std::cout << "Result : " << ret << std::endl;

		if ( ret == 0 ) {
			_running = false;
		}

		return ret;

	}
	else {
		return -14;
	}
	
}

void CurlProcess::set_URL( const std::string& url ) {

	_url = url;

}


const std::string& CurlProcess::get_URL() {
	return _url;
}

bool CurlProcess::add_POST_parameter( const std::string& key, const std::string& value ) {

	if ( key.size() > 0 ) {
		_POST_data[key] = urlencode(value);
		curl_easy_setopt( _curl, CURLOPT_POST, 1 );
		return true;
	}
	else {
		return false;
	}
}

bool CurlProcess::add_GET_parameter( const std::string& key, const std::string& value ) {

	if ( key.size() > 0 ) {
		_GET_data[key] = urlencode(value);
		return true;
	}
	else {
		return false;
	}
}

void CurlProcess::set_POST_data( const std::map<std::string,std::string>& data ) {
	
	if ( !data.empty() ) {
		_POST_data = data;
		curl_easy_setopt( _curl, CURLOPT_POST, 1 );
	}

}

void CurlProcess::set_GET_data( const std::map<std::string,std::string>& data ) {
	_GET_data = data;
}


void CurlProcess::add_form_file( const std::string& field_name, const std::string& file_path ) {

	curl_formadd(&_form_post,
	           &_form_end,
	           CURLFORM_COPYNAME, field_name.c_str(),
	           CURLFORM_FILE, file_path.c_str(),
	           CURLFORM_END);
	 
}

void CurlProcess::add_form_data( const std::string& field_name, const std::string& value ) {
	
	curl_formadd(&_form_post,
	       &_form_end,
	       CURLFORM_COPYNAME, field_name.c_str(),
	       CURLFORM_COPYCONTENTS, value.c_str(),
	       CURLFORM_END);

}


void CurlProcess::prepare() {

	/* Add Get data to URL */
	if ( !_GET_data.empty() ) {

		std::string data = concatenate_data( _GET_data );

		/* Add "?" only if it is not already present */
		_url += ( _url.find('?') == std::string::npos ? "?" : "" ) + data;

	}


	if ( _url.size() > 0 ) {
    	curl_easy_setopt( _curl, CURLOPT_URL, _url.c_str() );
	}

	/* Add Post data in Header */
	if ( !_POST_data.empty() ) {

		std::string data = concatenate_data( _POST_data );

		curl_easy_setopt( _curl, CURLOPT_COPYPOSTFIELDS, data.c_str() );

	}

	curl_easy_setopt( _curl, CURLOPT_WRITEDATA, this );
    curl_easy_setopt( _curl, CURLOPT_WRITEFUNCTION, &_callback_data_bumper);

}

void CurlProcess::send() {

	this->prepare();

	if ( _header_list != NULL ) {
		curl_easy_setopt( _curl, CURLOPT_HTTPHEADER, _header_list );
	}

   	_response_code = 1000;

   	_running = true;

    
    curl_easy_perform( _curl );
    curl_easy_getinfo( _curl, CURLINFO_HTTP_CODE, &_response_code );
    
    _running = false;

    this->_on_connection_closed( _response_code );

}

bool CurlProcess::is_running() const {
	return _running;
}


unsigned long CurlProcess::get_response_code() const {
	return _response_code;
}


const std::string CurlProcess::concatenate_data( const std::map<std::string,std::string>& data_source ) const {

	std::string data_str;
	std::map<std::string,std::string>::const_iterator it = data_source.begin();
	bool first = true;

	for ( it = data_source.begin() ; it != data_source.end(); it++ ) {
		
		data_str += ( !first ? "&" : "" ) + (*it).first;
		
		const std::string& value = (*it).second;
		if ( value.size() > 0 ) {
			data_str += "=" + (*it).second;
		}

		first = false;
		 

	}

	return data_str;

}
