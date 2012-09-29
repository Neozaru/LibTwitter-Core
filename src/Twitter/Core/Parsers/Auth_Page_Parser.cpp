#include "Auth_Page_Parser.h"

#include "../Utils.h"
#include "../OAuth.h"

Auth_Page_Parser::Auth_Page_Parser()  {

}

Auth_Page_Parser::~Auth_Page_Parser() {

}



bool Auth_Page_Parser::parse_page( const std::string& auth_page ) {


    const std::string& tokenFields = OAuthConsts::TOKEN_TWITTER_RESP_KEY;
	const std::string& authTokenFields = OAuthConsts::AUTHENTICITY_TOKEN_TWITTER_RESP_KEY;
    const std::string& endTag = OAuthConsts::TOKEN_END_TAG_TWITTER_RESP;

    // Now, let's find the authenticity token and oauth token
    size_t pos_start = auth_page.find( authTokenFields );
    if( pos_start == std::string::npos ) {
        return false;
    }

    pos_start += authTokenFields.length();
    size_t pos_end = auth_page.substr( pos_start ).find( endTag );
    if( pos_end == std::string::npos ) {
         return false;
    }


    _auth_token_value = auth_page.substr( pos_start, pos_end );

    pos_start = auth_page.find( tokenFields );
    if( std::string::npos == pos_start ) {
         return false;
    }
    pos_start += tokenFields.length();
    pos_end = auth_page.substr( pos_start ).find( endTag );
    if( std::string::npos == pos_end ) {
 
        return false;
    }

 
    _token_value = auth_page.substr( pos_start, pos_end );

    return true;   

}



std::string Auth_Page_Parser::get_token() {
	return _token_value;
}

std::string Auth_Page_Parser::get_auth_token() {
	return _auth_token_value;
}
