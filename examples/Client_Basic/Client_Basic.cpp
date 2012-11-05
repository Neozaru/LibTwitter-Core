
#include <Twitter/Core/TwitterSession.h>

#include <string>
#include <iostream>



int main( int argc, char** argv ) {


	bool auto_pin = false;


	if ( argc > 1 && std::string(argv[1]) == "auto" ) {
		auto_pin = true;
	}

	/* Creates new Session Object */
	TwitterSession* ts = new TwitterSession();


	/* *** */
	/* Set consummer keys and secrets. */
	/* It corresponds to your own app key/secret */
	/* *** */

	ts->get_oauth().set_consumer_key( "4wdGht7GCUYqMbLLsY8Yg" );
	ts->get_oauth().set_consumer_secret( "DmPp6hteK6bgR4JiKLbOqSFPNT0r35QFAlbRGjR3E" );

	/*************************************/


	const std::string& url = ts->generate_auth_URL();

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


		if ( !ts->bypass_PIN_with_password(url,username,password) ) {
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

		if ( !ts->authenticate_with_PIN_code( PIN_code ) ) {
			std::cout << "Could not authenticate you. Was PIN entered correctly ?" << std::endl;
			return -2;
		}

	}

	std::cout << "Authentication successful !" << std::endl;

	int request_id = ts->send_request( ts->verify_credentials_request() );

	if ( ts->get_request_response_code( request_id ) != e_HTTP_response_code::OK ) {

		std::cout << "Could not get last credential. :( Error " << ts->get_request_response_code( request_id )  << std::endl;
		return -3;

	}


	std::cout << "Press Ctrl+C to Quit, or type a new status : ";

	std::string status;
	std::cin >> status;

	std::cout << std::endl;


	if ( status.size() <= 0 ) {
		std::cout << "[QUIT]" << std::endl;
		return 0;
	}

	request_id = ts->send_request( ts->update_status_request( status ) );	

	if ( ts->get_request_response_code( request_id ) != e_HTTP_response_code::OK ) {

		std::cout << "Status not updated... Bad response code" << std::endl;

		return -3;
	}


	std::cout << "Status updated !" << std::endl;

	request_id = ts->send_request( ts->mentions_timeline_request() );

	if ( ts->get_request_response_code( request_id ) != e_HTTP_response_code::OK ) {

		std::cout << "Unable to get your timeline (code" << ts->get_request_response_code( request_id )  << ")" << std::endl;
		return -4;

	}
	else {

		/* Gets result data of the request */
		std::string timeline_json = ts->get_request_response_data( request_id );

		if ( timeline_json.size() > 0 ) {
			std::cout << "Received timeline : " << timeline_json << std::endl;
		}
		else {
			std::cout << "Received empty timeline. WTFException." << std::endl;
		}

	}


	return 0;

}
