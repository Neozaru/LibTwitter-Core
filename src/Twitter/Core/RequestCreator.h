#ifndef H_REQUEST_CREATOR_H
	#define H_REQUEST_CREATOR_H

	#include "TwitterConstants.h"

	/**
	* \namespace TwDefaults
	* \brief Default values in requests
	*/
	namespace TwDefaults {

		/**
		* \enum N_UN
		* \brief Undefined number (default value) 
		*/
		const int N_UN = -1;

		/**
		* \enum S_UN
		* \brief Undefined string (default value) 
		*/
		const std::string S_UN = "";

	};

	using namespace TwDefaults;

	class TwitterSession;
	class TwitterRequest;

	class GenericFactory {
	public:
		virtual TwitterRequest* create_request( const std::string& url = "" ) = 0;

	};

	/**
	* \class RequestFactory
	* \brief SubFactory of RequestCreator. 
	* Changed when user wants to create Subclasses of TwitterRequest
	*/
	template<typename RequestType = TwitterRequest>
	class RequestFactory : public GenericFactory {

	public:
		RequestFactory( TwitterSession* session ) : _session(session) {}
		~RequestFactory() {}

		TwitterRequest* create_request( const std::string& url = "" ) {
			return new RequestType(_session,url);
		}

	private:
		TwitterSession* _session;

	};


	/**
	* \class RequestCreator
	* \brief Main factory used to generate new TwitterRequests. Shouldn't be used.
	*
	* Methods <request_name>_request are automatically generated from a Python script
	* This system allow me (us ?) to add and edit requests very quickly, and avoid human errors
	*
	*/
	class RequestCreator {
	public:
		RequestCreator( GenericFactory* factory );
		~RequestCreator();

		/**
		* \fn __make_a_request
		* \brief Creates a new TwitterRequest, associated with Session
		* 
		* \param url Optional URL
		*
		* \return Created TwitterRequest
		*/
		TwitterRequest* __make_a_request( const std::string& url );

		/**
		* \fn set_next_request
		* \brief Defines next request Object
		*
		* \param req User instance for the next request
		*
		* Users who wants to create specific request objects must call
		* this method (or "change_requests_class() method")
		*
		*/
		void set_next_request( TwitterRequest* req );

		/**
		* \fn change_requests_class
		* \brief Defines next request Class
		*
		* \param <TwitterRequestClass> 
		*
		* Users who wants to create specific request objects must call
		* this method (or "set_next_request() method")
		*
		*/
		template <typename TwitterRequestClass>
		void change_requests_class() {
			_requests_factory = new RequestFactory<TwitterRequestClass>(this);
		}


		/************************/
		/* Twitter API Requests */
		/************************/

		/* See file "request_methods_generator.py" */

		TwitterRequest* update_status_request( const std::string& status,
								 int in_reply_to = N_UN,
								 bool display_coordinates = false,
								 bool trim_user = false
								 );

		TwitterRequest* stream_user_request( std::string with = "followings",
											std::string track = S_UN
											  );

		TwitterRequest* verify_credentials_request();

		TwitterRequest* get_settings_request();


/* BEGIN_PYGEN don't remove this comment (2012/9/25 23:11) */
/* Doc here for "mentions_timeline"  */
TwitterRequest* mentions_timeline_request( int count = 20, 
										int since_id = N_UN, 
										int max_id = N_UN, 
										bool trim_user = false, 
										bool contributor_details = false, 
										bool include_entities = true );

TwitterRequest* user_timeline_request( int user_id = N_UN, 
										std::string screen_name = S_UN, 
										int count = N_UN, 
										int since_id = N_UN, 
										int max_id = N_UN, 
										bool trim_user = false, 
										bool exclude_replies = false, 
										bool contributor_details = false, 
										bool include_rts = true );


TwitterRequest* home_timeline_request( int count = N_UN, 
										int since_id = N_UN, 
										int max_id = N_UN, 
										bool trim_user = false, 
										bool exclude_replies = false, 
										bool contributor_details = false, 
										bool include_entities = true );

/* END_PYGEN don't remove this comment (2012/9/25 23:11) */


	protected:
		

		GenericFactory* _requests_factory;

		TwitterRequest* _next_request;

	};

#endif /* H_REQUEST_CREATOR_H */