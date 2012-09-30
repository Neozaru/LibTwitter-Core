
#ifndef H_TWITTERSESSION_H
	#define H_TWITTERSESSION_H

	#include "OAuth.h"
	#include "TwitterConstants.h"
	#include "TwitterRequestListener.h"
	#include "RequestCreator.h"

	#include <map>
	#include <vector>
	#include <string>



	class TwitterRequest;

	//using namespace TwDefaults;
	/**
	* \class TwitterSession TwitterSession.h
	* \brief Represents an user Twitter session.
	* Used for login and sends requests to Twitter
	*/
	//template<typename RequestType = TwitterRequest>
	class TwitterSession : public TwitterRequestListener, public RequestCreator {
	public:

		/**
		* \fn TwitterSession
		* \brief Contructor. Does absolutely nothing else
		*/
		TwitterSession();

		/**
		* \fn ~TwitterSession
		* \brief Destructor. Closes all Twitter communications and requests
		*/
		~TwitterSession();

		/**
		* \fn set_asynchronous
		* \brief Configure if requests sent via this Objet will be blocking or non-blocking
		* Default is synchronous (blocking) 
		*
		* \param async Flag to set (true for asynchronous, or false for synchronous)
		*/
		void set_asynchronous( bool async );

		/**
		* \fn set_HTTP_proxy
		* \brief Sets a proxy for all future HTTP requests.
		*
		* \param proxy String containing proxy description.
		*
		* Syntax for "proxy" parameter : <protocol>://[<username>[:<password>]@]<proxy_adress>[:<port>]
		* If "port" is not included in proxy description, default port will be set (1080)
		* If you enter an empty String as proxy description (""), LibTwitter will disable proxy, including from your System settings
		*
		* Example : "http://my.proxy.com:3128" (connect to my.proxy.com with port 3128)
		*/
		void set_HTTP_proxy( const std::string& proxy );

		/**
		* \fn get_HTTP_proxy
		* \brief Returns current HTTP proxy previously set by "set_HTTP_proxy"
		*
		* It will not consider System Proxy environment variable.
		*/
		const std::string& get_HTTP_proxy() const;
		
		/**
		* \fn generate_auth_URL
		* \brief Queries Twitter for an authorization URL
		* In standards, authorization URL is visited by user, which authorizes application
		*
		* \return Generated URL
		*/
		std::string generate_auth_URL();

		/**
		* \fn authenticate_with_PIN_code
		* \brief Query Twitter for authentication with PIN_Code
		*
		* \param PIN_code PIN Code displayed on authorization page
		*
		* \return true if authentication was successfull, false otherwise
		*
		*/
		bool authenticate_with_PIN_code( const std::string& PIN_code );

		/**
		* \fn bypass_PIN_with_password
		* \brief Simulates visit of authorization URL by user, and auto-authorize the app
		* Created to simplify user connection, but requires username and password.
		*
		* \param auth_URL Authorization URL (usally generated from generate_auth_URL())
		* \param username Twitter username or email address
		* \param password Twitter user password
		*
		* \return true is operation was successful, false otherwise
		*
		* This methods calls automatically "authenticate_with_PIN_code" method
		*
		*/
		bool bypass_PIN_with_password( const std::string& auth_URL, const std::string& user, const std::string& password );

		/**
		* \fn send_request
		* \brief Sends a TwitterRequest, and stores it in this session
		*
		* \param request Request to send and handle.
		*
		* \return A generated request ID. Can be saved in order to retrieve the request later and get response
		* NOTE : It is also possible to send a request directly (request->send())		
		*/
		int send_request( TwitterRequest* request );

		/**
		* \fn get_request_response_code
		* \brief Gets HTTP response code of a sent request.
		*
		* \param Request ID
		*
		* \return HTTP response code of the request (200 == OK), WAITING_RESPONSE if request was not sent, UNDEFINED if request doesn't exists
		*
		* NOTE : It is also possible to send a request directly (request->get_response_code())
		*/
		unsigned long get_request_response_code( int request_id );

		/**
		* \fn get_request_response_data
		* \brief Gets HTTP response code of a sent request.
		*
		* \param request_id Request ID generated if "send_request" was used from TwitterSession
		* \param delete_request If sets to "true" (default), the request and its buffer will be deleted
		*
		* \return A buffer containing raw (JSON) response of the TwitterRequest. (can be result, or error description)
		* NOTE : It is also possible to send a request directly (request->get_response_data())
		*/
		std::string get_request_response_data( int request_id,  bool delete_request = true );


		/**
		* \fn get_oauth
		* \brief Gets OAuth object, used to authenficate users in the Twitter API
		* OAuth object is provided or inspired from TwitCurl. ( \url https://code.google.com/p/twitcurl/ )
		* It is and will be modified in order to improve performance and readability with LibTwitter.
		*
		* \return OAuth object, containing user authentication informations
		*/
		OAuth& get_oauth();


		/**
		* \fn set_debug_mode
		* \brief Enable test/debug mode. When sets to "true", received data and headers will be printed to stdout
		*
		* \param debug Flag to set ("true" for debug_mode, "false" for normal_mode)
		*
		* See "Utils::debug(*)" calls in source code" 
		*
		*/ 
		void set_debug_mode( char debug );


		template <typename TwitterRequestClass>
		void change_requests_class() {
			_requests_factory = new RequestFactory<TwitterRequestClass>(this);
		}

	protected:

		/**************/
		/* ATTRIBUTES */
		/**************/

		std::map<int,TwitterRequest*> _requests_map;
		std::map<TwitterRequest*,int> _reverse_requests_map;

		std::string _username;

		bool _asynchronous;
		OAuth _oauth;

		int _request_counter;


		std::string _http_proxy;


		bool isDefined( int value );
		bool isDefined( std::string value );

		/**
		* \fn on_request_data_received
		* \brief Default callback when data is received for a request
		*
		* \param request_id ID of the concerned request
		* \param data Received data
		*
		*/
		virtual void on_request_data_received( int request_id, const std::string& data ) {}

		/**
		* \fn on_request_connection_closed
		* \brief Default callback when request is closed
		*
		* \param request_id ID of the concerned request
		* \param data Returned HTTP response code
		*
		*/
		virtual void on_request_connection_closed( int request_id, unsigned long response_code ) {}



	private:

		/**
		* \fn _on_request_data_received
		* \brief Callback bumper function. Calls on_request_data_received(id_request,data)
		*
		* This function is automatically called by TwitterRequest::_on_data_received()
		*/
		void on_request_data_received( TwitterRequest* request, const std::string& data );

		/**
		* \fn _on_request_data_received
		* \brief Callback bumper function. Calls on_request_connection_closed(id_request,response_code)
		*
		* This function is automatically called by TwitterRequest::_on_data_received()
		*/
		void on_request_connection_closed( TwitterRequest* request, unsigned long response_code );
		
		/**
		* \fn get_request_id
		* \brief Internal method used to retrieve request ID from pointer.
		*
		* \param request Request pointer
		*
		* \return ID of existing request. -1 otherwise
		*
		*/
		int get_request_id( TwitterRequest* request );


	};




#endif