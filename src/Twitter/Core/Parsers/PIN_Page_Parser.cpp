#include "PIN_Page_Parser.h"

#include "../Utils.h"
#include "../OAuth.h"

PIN_Page_Parser::PIN_Page_Parser() {

}

PIN_Page_Parser::~PIN_Page_Parser() {

}


bool PIN_Page_Parser::parse_page( const std::string& pin_page ) {


	const std::string& pinField = OAuthConsts::PIN_TWITTER_RESP_KEY;
	const std::string& pinEndTag = OAuthConsts::PIN_END_TAG_TWITTER_RESP;

    // Now, let's find the PIN CODE
    size_t pos_start = pin_page.find( pinField );
    if( std::string::npos == pos_start ) {
        return false;
    }
    
    pos_start += pinField.length();
    size_t pos_end = pin_page.substr( pos_start ).find( pinEndTag );
    if( std::string::npos == pos_end ) {
        return false;
    }

    _pin_code = pin_page.substr( pos_start, pos_end );
    
    return true;

}


std::string PIN_Page_Parser::get_PIN_code() {
    return _pin_code;
}