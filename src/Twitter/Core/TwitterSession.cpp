#include "TwitterSession.h"

#include "TwitterRequest.h"
#include "CurlProcess.h"
#include "Utils.h"

#include "Parsers/Auth_Page_Parser.h"
#include "Parsers/PIN_Page_Parser.h"

char _g_debug_mode;

TwitterSession::TwitterSession() 
		: RequestCreator(new RequestFactory<TwitterRequest>(this)),
		 _request_counter(0),
		 _http_proxy(DEFAULT_PROXY) {

	_g_debug_mode = NONE;

}

TwitterSession::~TwitterSession() {

}


OAuth& TwitterSession::get_oauth() {
	return _oauth;
}


void TwitterSession::set_asynchronous( bool async ) {
	_asynchronous = async;
}

void TwitterSession::set_HTTP_proxy( const std::string& proxy ) {

	_http_proxy = proxy;

}

const std::string& TwitterSession::get_HTTP_proxy() const {
	return _http_proxy;
}

bool TwitterSession::isDefined( int value ) {
	return ( value != DEF_NUM );
}


bool TwitterSession::isDefined( std::string value ) {
	return ( value != DEF_STR );
}


int TwitterSession::send_request( TwitterRequest* tr ) {
	
	_requests_map[++_request_counter] = tr;
	_reverse_requests_map[tr] = _request_counter;

	if ( _asynchronous ) {
		tr->send_async();
	}
	else {
		tr->send();
	}

	return _request_counter;

}

unsigned long TwitterSession::get_request_response_code( int request_id ) {

	TwitterRequest* tr = _requests_map[ request_id ];
	
	if ( tr != NULL ) {
		return tr->get_response_code();
	}



	return false;

}

std::string TwitterSession::get_request_response_data( int request_id, bool delete_request ) {

	TwitterRequest* tr = _requests_map[ request_id ];


	if ( tr !=  NULL && tr->get_response_code() < e_HTTP_response_code::UNDEFINED ) {
		std::string ret( tr->get_response_data() );
		
		if ( delete_request ) {
			
			_reverse_requests_map.erase(tr);
			_requests_map[ request_id ] = NULL;
			delete tr;

			Utils::debug("Request " + Utils::otos(request_id) + " successfully deleted");

		}

		return ret;
	}
	else {
		return "";
	}

}


void TwitterSession::on_request_data_received( TwitterRequest* request, const std::string& data ) {

	int request_id = this->get_request_id(request);

	if ( request_id != -1 ) {

		this->on_request_data_received( request_id, data );

	}

}

void TwitterSession::on_request_connection_closed( TwitterRequest* request, unsigned long response_code ) {

	int request_id = this->get_request_id(request);

	if ( request_id != -1 ) {

		this->on_request_connection_closed( request_id, response_code );

	}

}



std::string TwitterSession::generate_auth_URL() {

	TwitterRequest* tr = new TwitterRequest(this,"http://"+OAuthConsts::TWITTER_REQUEST_TOKEN_URL);
	tr->send();

	unsigned long code = tr->get_response_code();

	if ( code == e_HTTP_response_code::OK ) {

		std::string response = tr->get_response_data();

        _oauth.extract_oauth_token_key_secret( response );

        const std::string& oAuth_TokenKey = _oauth.get_token_key();

        std::string auth_URL;

        auth_URL.assign( "http://" + OAuthConsts::TWITTER_AUTHORIZE_URL 
        							+ oAuth_TokenKey.c_str() );

        return auth_URL;

	}
	else {
		return Utils::otos(code);
	}

}

bool TwitterSession::authenticate_with_PIN_code( const std::string& PIN_code ) {

  /* Insert PIN Code in current OAuth configuration */
	_oauth.set_PIN_code( PIN_code );
	
	const std::string access_url = "http://" + OAuthConsts::TWITTER_ACCESS_TOKEN_URL;
	TwitterRequest* access_tr = new TwitterRequest(this,access_url);

	/* With PIN Code, we can now ask directly Twitter for access */
	access_tr->send();

	if ( access_tr->get_response_code() == e_HTTP_response_code::OK ) {

		const std::string& valid_page = access_tr->get_response_data();

		/* App receives secret key, and can now send requests */
		/* App should save this key on client side */
		if ( _oauth.extract_oauth_token_key_secret( valid_page ) ) {

			return true;

		}

	}

	/* If HTTP request or PIN auth fails */
	return false;


}


bool TwitterSession::bypass_PIN_with_password( const std::string& auth_URL, const std::string& user, const std::string& password ) {

    Utils::debug("[PIN] HANDLING");

    TwitterRequest* get_auth_page_tr = new TwitterRequest( this, auth_URL );

    /* Query for Twitter Authentification Web Page http request */
   	get_auth_page_tr->send();

    if( get_auth_page_tr->get_response_code() == e_HTTP_response_code::OK ) {

    	std::string auth_page = get_auth_page_tr->get_response_data();
    	
    	Auth_Page_Parser auth_page_parser;

    	/* Parser will search for validation form in HTML source code */
        if ( auth_page_parser.parse_page( auth_page ) ) {

		    TwitterRequest* auth_tr = new TwitterRequest( this, auth_URL );

		    auth_tr->add_POST_parameter( OAuthConsts::TOKEN_KEY, auth_page_parser.get_token() );
		    auth_tr->add_POST_parameter( OAuthConsts::AUTHENTICITY_TOKEN_KEY, auth_page_parser.get_auth_token() );
		    auth_tr->add_POST_parameter( OAuthConsts::SESSIONUSERNAME_KEY, user );
		    auth_tr->add_POST_parameter( OAuthConsts::SESSIONPASSWORD_KEY, password );

		    /* Sends the form, as if the user clicked on "Allow Application" */
		    auth_tr->send();


		    if( auth_tr->get_response_code() == e_HTTP_response_code::OK )  {


	    		std::string pin_page = auth_tr->get_response_data();

	    		PIN_Page_Parser pin_page_parser;

	    		/* Now, a PIN is displayed somewhere on HTML page. Go find it ! */
	    		if ( pin_page_parser.parse_page( pin_page ) ) {

	    			const std::string& PIN_code = pin_page_parser.get_PIN_code();
		            Utils::debug("<<<< PIN found : " + PIN_code + " >>>>");

		       
    				if ( this->authenticate_with_PIN_code(PIN_code) ) {

    					const std::string& username = _oauth.get_username();
    					Utils::debug( "Identified as " + username );
    					return true;

    				}
    				else {
    					return false;
    				}

	    			

	    		}

	        }
	    }
    }
    

    return false;
}


int TwitterSession::get_request_id( TwitterRequest* request ) {

		if ( request != NULL ) {

			std::map<TwitterRequest*,int>::iterator iter = _reverse_requests_map.find(request);

			if ( iter != _reverse_requests_map.end() ) {

				return (*iter).second;

			}

	}

	return -1;
}


void TwitterSession::set_debug_mode( char debug ) {
	
	_g_debug_mode = debug;

}
