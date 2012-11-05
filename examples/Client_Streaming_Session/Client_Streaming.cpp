
#include <Twitter/Core/TwitterRequest.h>
#include "MyTwitterSession.h"


#include <string>
#include <iostream>



int main( int argc, char** argv ) {


	bool auto_pin = false;


	if ( argc > 1 && std::string(argv[1]) == "auto" ) {
		auto_pin = true;
	}

	/* Creates new Session Object */
	MyTwitterSession* mts = new MyTwitterSession();


	/* *** */
	/* Set consummer keys and secremts. */
	/* It corresponds to your own app key/secret */
	/* *** */

	mts->get_oauth().set_consumer_key( "4wdGht7GCUYqMbLLsY8Yg" );
	mts->get_oauth().set_consumer_secret( "DmPp6hteK6bgR4JiKLbOqSFPNT0r35QFAlbRGjR3E" );

	/*************************************/


	const std::string& url = mts->generate_auth_URL();

	/* If you get this error, check your app consumer_key/secret */
	if ( url.size() <= 0 ) {
		std::cout << "Authentication URL not found ! :'(" << std::endl;
		return -1;
	}

	/* User can go to this URL, authorize the app, and paste the PIN code obtained */
	std::cout << "Authentication URL : " << url << std::endl;
	
	if ( auto_pin ) {

		std::cout << "Will auto-connection you. Please enter login information." << std::endl;

		std::string username;
		std::string password;

		std::cout << "Username (screen name) : ";
		std::cin >> username;

		std::cout << "Password : ";
		std::cin >> password;


		if ( !mts->bypass_PIN_with_password(url,username,password) ) {
			std::cout << "Could not authenticate you. Was login correct ?" << std::endl;
			return -2;
		}

	}
	else {

		std::cout << "Please click or copy/paste the above link, to authorize this app" << std::endl;

		std::string PIN_code;


		while ( PIN_code.size() <= 0 ) {

			std::cout << "Enter received PIN code : ";

			std::cin >>  PIN_code;
			std::cout << std::endl;

		}

		if ( !mts->authenticate_with_PIN_code( PIN_code ) ) {
			std::cout << "Could not authenticate you. Was PIN entered correctly ?" << std::endl;
			return -2;
		}

	}

	/*
	* Here is a difference between Basic and Alternative Client
	*/

	std::cout << "Authentication successful !" << std::endl;

	/* Create yourself a TwitterRequest object */
	TwitterRequest* tr_verify_cred = mts->verify_credentials_request();
	
	/* Call "send" to execute request */
	tr_verify_cred->send();

	/* Grab response code directly from the request */
	if ( tr_verify_cred->get_response_code() != e_HTTP_response_code::OK ) {

		std::cout << "Could not authenticate you. Was PIN entered correctly ?" << std::endl;
		return -3;

	}
	
	/* Let MyTwitterSession handle the request */
	/* See MyTwitterSession.h */
	mts->send_request( mts->user_stream_request() );


	return 0;

}