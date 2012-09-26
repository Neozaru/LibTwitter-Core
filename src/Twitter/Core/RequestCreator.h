#ifndef H_REQUEST_CREATOR_H
	#define H_REQUEST_CREATOR_H

	#include "TwitterConstants.h"

	typedef std::string tid_t;
	typedef unsigned int uid_t;

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

/*
		TwitterRequest* update_status_request( const std::string& status,
								 int in_reply_to = N_UN,
								 bool display_coordinates = false,
								 bool trim_user = false
								 );
*/

		TwitterRequest* stream_user_request( std::string with = "followings",
											std::string track = S_UN
											  );

		TwitterRequest* verify_credentials_request();

		TwitterRequest* get_settings_request();


/* BEGIN_PYGEN don't remove this comment (2012/9/26 22:31) */
/* Doc here for "mentions_timeline"  */
TwitterRequest* mentions_timeline_request( int count = 20, 
										uid_t since_id = N_UN, 
										int max_id = N_UN, 
										bool trim_user = false, 
										bool contributor_details = false, 
										bool include_entities = true );

TwitterRequest* user_timeline_request( int user_id = N_UN, 
										const std::string& screen_name = S_UN, 
										int count = N_UN, 
										uid_t since_id = N_UN, 
										int max_id = N_UN, 
										bool trim_user = false, 
										bool exclude_replies = false, 
										bool contributor_details = false, 
										bool include_rts = true );


TwitterRequest* home_timeline_request( int count = N_UN, 
										uid_t since_id = N_UN, 
										int max_id = N_UN, 
										bool trim_user = false, 
										bool exclude_replies = false, 
										bool contributor_details = false, 
										bool include_entities = true );

TwitterRequest* retweets_request( uid_t id, 
										int count = 50, 
										bool trim_user = false );

TwitterRequest* destroy_status_request( uid_t id, 
										bool trim_user = false );

TwitterRequest* update_status_request( const std::string& status, 
										const std::string& in_reply_to_status_id = S_UN, 
										const std::string& place_id = S_UN, 
										bool display_coordinates = false, 
										bool trim_user = false, 
										float lat = N_UN, 
										float lon = N_UN );

TwitterRequest* retweet_request( uid_t id, 
										bool trim_user = false );

TwitterRequest* oembed_status_request( uid_t id, 
										const std::string& url, 
										int maxwidth = N_UN, 
										bool hide_media = false, 
										bool hide_thread = false, 
										bool omit_script = false, 
										const std::string& align = "center", 
										const std::string& related = S_UN, 
										const std::string& lang = S_UN );


TwitterRequest* search_tweets_request( const std::string& q, 
										const std::string& locale = S_UN, 
										const std::string& result_type = S_UN, 
										int count = N_UN, 
										const std::string& until = S_UN, 
										uid_t since_id = N_UN, 
										const std::string& max_id = S_UN, 
										bool include_entities = true, 
										const std::string& callback = S_UN );

TwitterRequest* sent_direct_messages_request( int count = N_UN, 
										int page = N_UN, 
										uid_t since_id = N_UN, 
										const std::string& max_id = S_UN, 
										bool include_entities = true );

TwitterRequest* show_direct_messages_request( uid_t id );

TwitterRequest* destroy_direct_messages_request( uid_t id, 
										bool include_entities = true );

TwitterRequest* new_direct_message_by_user_id_request( const std::string& user_id, 
										const std::string& text );


TwitterRequest* new_direct_message_by_screen_name_request( const std::string& screen_name, 
										const std::string& text );

TwitterRequest* friends_ids_request( uid_t user_id, 
										bool stringify_ids = true );

TwitterRequest* friends_ids_request( const std::string& screen_name, 
										bool stringify_ids = true );

TwitterRequest* followers_ids_request( uid_t user_id, 
										bool stringify_ids = true );

TwitterRequest* followers_ids_request( const std::string& screen_name, 
										bool stringify_ids = true );

/*
You SHOULD pass user ids or screen names in a "comma,sepa,rated,string"
*/
TwitterRequest* lookup_friendship_by_names_request( const std::string& screen_name );

/*
You SHOULD pass user ids or screen names in a "comma,sepa,rated,string"
*/
TwitterRequest* lookup_friendship_by_ids_request( const std::string& user_id );

TwitterRequest* incoming_friendships_request( bool stringify_ids = true );

TwitterRequest* outgoing_friendships_request( bool stringify_ids = true );

TwitterRequest* create_friendship_request( const std::string& screen_name, 
										bool follow = true );

TwitterRequest* create_friendship_request( uid_t user_id, 
										bool follow = true );

TwitterRequest* destroy_friendship_request( const std::string& screen_name );

TwitterRequest* destroy_friendship_request( uid_t user_id );

TwitterRequest* update_friendship_request( const std::string& screen_name, 
										bool retweets, 
										bool device );

TwitterRequest* update_friendship_request( uid_t user_id, 
										bool retweets, 
										bool device );

TwitterRequest* show_friendship_request( uid_t source_id, 
										uid_t target_id );


TwitterRequest* show_friendship_request( const std::string& source_screen_name, 
										const std::string& target_screen_name );

/* END_PYGEN don't remove this comment (2012/9/26 22:31) */


	protected:
		

		GenericFactory* _requests_factory;

		TwitterRequest* _next_request;

	};

#endif /* H_REQUEST_CREATOR_H */