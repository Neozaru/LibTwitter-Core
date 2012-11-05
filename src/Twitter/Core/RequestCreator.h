#ifndef H_REQUEST_CREATOR_H
	#define H_REQUEST_CREATOR_H


	#include <list>

	#include "TwitterConstants.h"


	/**
	* \namespace TwDefaults
	* \brief Default values in requests
	*/
	namespace TwDefaults {

		/**
		* \enum DEF_NUM
		* \brief Undefined number (default value) 
		*/
		const int DEF_NUM = -1;

		/**
		* \enum DEF_STR
		* \brief Undefined string (default value) 
		*/
		const std::string DEF_STR = "";

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


/* BEGIN_PYGEN don't remove this comment (2012/10/27 14:35) */
/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/statuses/mentions_timeline">Twitter Documentation for [mentions_timeline]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/statuses/mentions_timeline}{Twitter Documentation for [mentions\_timeline]}
* \endlatexonly
*/
/* Doc here for "mentions_timeline"  */
TwitterRequest* mentions_timeline_request( int count = 20, 
										usr_id_t since_id = DEF_STR, 
										int max_id = DEF_NUM, 
										bool trim_user = false, 
										bool contributor_details = false, 
										bool include_entities = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/statuses/user_timeline">Twitter Documentation for [user_timeline_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/statuses/user_timeline}{Twitter Documentation for [user\_timeline\_by\_id]}
* \endlatexonly
*/
TwitterRequest* user_timeline_by_id_request( usr_id_t user_id, 
										int count = DEF_NUM, 
										twt_id_t since_id = DEF_STR, 
										twt_id_t max_id = DEF_STR, 
										bool trim_user = false, 
										bool exclude_replies = false, 
										bool contributor_details = false, 
										bool include_rts = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/statuses/user_timeline">Twitter Documentation for [user_timeline]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/statuses/user_timeline}{Twitter Documentation for [user\_timeline]}
* \endlatexonly
*/
TwitterRequest* user_timeline_request( usr_name_t screen_name, 
										int count = DEF_NUM, 
										twt_id_t since_id = DEF_STR, 
										twt_id_t max_id = DEF_STR, 
										bool trim_user = false, 
										bool exclude_replies = false, 
										bool contributor_details = false, 
										bool include_rts = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/statuses/home_timeline">Twitter Documentation for [home_timeline]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/statuses/home_timeline}{Twitter Documentation for [home\_timeline]}
* \endlatexonly
*/

TwitterRequest* home_timeline_request( int count = DEF_NUM, 
										usr_id_t since_id = DEF_STR, 
										int max_id = DEF_NUM, 
										bool trim_user = false, 
										bool exclude_replies = false, 
										bool contributor_details = false, 
										bool include_entities = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/statuses/retweets/:id">Twitter Documentation for [get_retweets]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/statuses/retweets/:id}{Twitter Documentation for [get\_retweets]}
* \endlatexonly
*/
TwitterRequest* get_retweets_request( twt_id_t id, 
										int count = 50, 
										bool trim_user = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/statuses/show/:id">Twitter Documentation for [show_status]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/statuses/show/:id}{Twitter Documentation for [show\_status]}
* \endlatexonly
*/
TwitterRequest* show_status_request( twt_id_t id, 
										bool include_my_retweet = true, 
										bool trim_user = false, 
										bool include_entities = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/statuses/destroy/:id">Twitter Documentation for [destroy_status]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/statuses/destroy/:id}{Twitter Documentation for [destroy\_status]}
* \endlatexonly
*/
TwitterRequest* destroy_status_request( twt_id_t id, 
										bool trim_user = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/statuses/update">Twitter Documentation for [update_status]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/statuses/update}{Twitter Documentation for [update\_status]}
* \endlatexonly
*/
TwitterRequest* update_status_request( str_t status, 
										str_t in_reply_to_status_id = DEF_STR, 
										str_t place_id = DEF_STR, 
										bool display_coordinates = false, 
										bool trim_user = false, 
										float lat = DEF_NUM, 
										float lon = DEF_NUM );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/statuses/retweet/:id">Twitter Documentation for [retweet]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/statuses/retweet/:id}{Twitter Documentation for [retweet]}
* \endlatexonly
*/


TwitterRequest* retweet_request( twt_id_t id, 
										bool trim_user = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/statuses/oembed">Twitter Documentation for [oembed_status]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/statuses/oembed}{Twitter Documentation for [oembed\_status]}
* \endlatexonly
*/
TwitterRequest* oembed_status_request( twt_id_t id, 
										str_t url, 
										int maxwidth = DEF_NUM, 
										bool hide_media = false, 
										bool hide_thread = false, 
										bool omit_script = false, 
										str_t align = "center", 
										str_t related = DEF_STR, 
										lang_t lang = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/search/tweets">Twitter Documentation for [search_tweets]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/search/tweets}{Twitter Documentation for [search\_tweets]}
* \endlatexonly
*/

TwitterRequest* search_tweets_request( str_t q, 
										str_t locale = DEF_STR, 
										str_t result_type = DEF_STR, 
										int count = DEF_NUM, 
										str_t until = DEF_STR, 
										twt_id_t since_id = DEF_STR, 
										twt_id_t max_id = DEF_STR, 
										bool include_entities = true, 
										str_t callback = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/direct_messages/sent">Twitter Documentation for [sent_direct_messages]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/direct_messages/sent}{Twitter Documentation for [sent\_direct\_messages]}
* \endlatexonly
*/
TwitterRequest* sent_direct_messages_request( int count = DEF_NUM, 
										int page = DEF_NUM, 
										usr_id_t since_id = DEF_STR, 
										str_t max_id = DEF_STR, 
										bool include_entities = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/direct_messages/show">Twitter Documentation for [show_direct_messages]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/direct_messages/show}{Twitter Documentation for [show\_direct\_messages]}
* \endlatexonly
*/
TwitterRequest* show_direct_messages_request( msg_id_t id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/direct_messages/destroy">Twitter Documentation for [destroy_direct_messages]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/direct_messages/destroy}{Twitter Documentation for [destroy\_direct\_messages]}
* \endlatexonly
*/
TwitterRequest* destroy_direct_messages_request( msg_id_t id, 
										bool include_entities = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/direct_messages/new">Twitter Documentation for [new_direct_message_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/direct_messages/new}{Twitter Documentation for [new\_direct\_message\_by\_id]}
* \endlatexonly
*/
TwitterRequest* new_direct_message_by_id_request( usr_id_t user_id, 
										str_t text );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/direct_messages/new">Twitter Documentation for [new_direct_message]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/direct_messages/new}{Twitter Documentation for [new\_direct\_message]}
* \endlatexonly
*/

TwitterRequest* new_direct_message_request( usr_name_t screen_name, 
										str_t text );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/friends/ids">Twitter Documentation for [friends_ids_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/friends/ids}{Twitter Documentation for [friends\_ids\_by\_id]}
* \endlatexonly
*/
TwitterRequest* friends_ids_by_id_request( usr_id_t user_id, 
										bool stringify_ids = true, 
										cur_id_t cursor = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/friends/ids">Twitter Documentation for [friends_ids]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/friends/ids}{Twitter Documentation for [friends\_ids]}
* \endlatexonly
*/
TwitterRequest* friends_ids_request( usr_name_t screen_name, 
										bool stringify_ids = true, 
										cur_id_t cursor = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/followers/ids">Twitter Documentation for [followers_ids_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/followers/ids}{Twitter Documentation for [followers\_ids\_by\_id]}
* \endlatexonly
*/
TwitterRequest* followers_ids_by_id_request( usr_id_t user_id, 
										bool stringify_ids = true, 
										cur_id_t cursor = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/followers/ids">Twitter Documentation for [followers_ids]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/followers/ids}{Twitter Documentation for [followers\_ids]}
* \endlatexonly
*/
TwitterRequest* followers_ids_request( usr_name_t screen_name, 
										bool stringify_ids = true, 
										cur_id_t cursor = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/friendships/lookup">Twitter Documentation for [lookup_friendship]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/friendships/lookup}{Twitter Documentation for [lookup\_friendship]}
* \endlatexonly
*/
/*
You SHOULD pass user ids or screen names in a "comma,sepa,rated,string"
*/
TwitterRequest* lookup_friendship_request( usr_name_t screen_name );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/friendships/lookup">Twitter Documentation for [lookup_friendship_by_ids]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/friendships/lookup}{Twitter Documentation for [lookup\_friendship\_by\_ids]}
* \endlatexonly
*/
/*
You SHOULD pass user ids or screen names in a "comma,sepa,rated,string"
*/
TwitterRequest* lookup_friendship_by_ids_request( usr_id_t user_id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/friendships/incoming">Twitter Documentation for [incoming_friendships]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/friendships/incoming}{Twitter Documentation for [incoming\_friendships]}
* \endlatexonly
*/
TwitterRequest* incoming_friendships_request( bool stringify_ids = true, 
										cur_id_t cursor = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/friendships/outgoing">Twitter Documentation for [outgoing_friendships]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/friendships/outgoing}{Twitter Documentation for [outgoing\_friendships]}
* \endlatexonly
*/
TwitterRequest* outgoing_friendships_request( bool stringify_ids = true, 
										cur_id_t cursor = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/friendships/create">Twitter Documentation for [create_friendship]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/friendships/create}{Twitter Documentation for [create\_friendship]}
* \endlatexonly
*/
TwitterRequest* create_friendship_request( usr_name_t screen_name, 
										bool follow = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/friendships/create">Twitter Documentation for [create_friendship_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/friendships/create}{Twitter Documentation for [create\_friendship\_by\_id]}
* \endlatexonly
*/
TwitterRequest* create_friendship_by_id_request( usr_id_t user_id, 
										bool follow = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/friendships/destroy">Twitter Documentation for [destroy_friendship]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/friendships/destroy}{Twitter Documentation for [destroy\_friendship]}
* \endlatexonly
*/
TwitterRequest* destroy_friendship_request( usr_name_t screen_name );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/friendships/destroy">Twitter Documentation for [destroy_friendship_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/friendships/destroy}{Twitter Documentation for [destroy\_friendship\_by\_id]}
* \endlatexonly
*/
TwitterRequest* destroy_friendship_by_id_request( usr_id_t user_id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/friendships/update">Twitter Documentation for [update_friendship]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/friendships/update}{Twitter Documentation for [update\_friendship]}
* \endlatexonly
*/
TwitterRequest* update_friendship_request( usr_name_t screen_name, 
										bool retweets, 
										bool device );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/friendships/update">Twitter Documentation for [update_friendship_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/friendships/update}{Twitter Documentation for [update\_friendship\_by\_id]}
* \endlatexonly
*/
TwitterRequest* update_friendship_by_id_request( usr_id_t user_id, 
										bool retweets, 
										bool device );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/friendships/show">Twitter Documentation for [show_friendship]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/friendships/show}{Twitter Documentation for [show\_friendship]}
* \endlatexonly
*/
TwitterRequest* show_friendship_request( usr_name_t source_screen_name, 
										usr_name_t target_screen_name );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/friendships/show">Twitter Documentation for [show_friendship_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/friendships/show}{Twitter Documentation for [show\_friendship\_by\_id]}
* \endlatexonly
*/

TwitterRequest* show_friendship_by_id_request( usr_id_t source_id, 
										usr_id_t target_id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/account/verify_credentials">Twitter Documentation for [verify_credentials]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/account/verify_credentials}{Twitter Documentation for [verify\_credentials]}
* \endlatexonly
*/
TwitterRequest* verify_credentials_request( bool include_entities = true, 
										bool skip_status = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/account/settings">Twitter Documentation for [set_account_settings]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/account/settings}{Twitter Documentation for [set\_account\_settings]}
* \endlatexonly
*/
TwitterRequest* set_account_settings_request( bool sleep_time_enabled = false, 
										int start_sleep_time = DEF_NUM, 
										int end_sleep_time = DEF_NUM, 
										lang_t lang = DEF_STR, 
										str_t time_zone = DEF_STR, 
										int trend_location_woeid = DEF_NUM );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/account/update_delivery_device">Twitter Documentation for [update_delivery_device]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/account/update_delivery_device}{Twitter Documentation for [update\_delivery\_device]}
* \endlatexonly
*/
TwitterRequest* update_delivery_device_request( str_t device = "none", 
										bool include_entities = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/account/update_profile">Twitter Documentation for [update_profile]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/account/update_profile}{Twitter Documentation for [update\_profile]}
* \endlatexonly
*/
TwitterRequest* update_profile_request( str_t name = DEF_STR, 
										str_t description = DEF_STR, 
										str_t url = DEF_STR, 
										bool include_entities = true, 
										bool skip_status = false, 
										str_t location = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/account/update_profile_background_image">Twitter Documentation for [update_profile_background_image]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/account/update_profile_background_image}{Twitter Documentation for [update\_profile\_background\_image]}
* \endlatexonly
*/
TwitterRequest* update_profile_background_image_request( bool use = true, 
										str_t image = DEF_STR, 
										bool tile = true, 
										bool skip_status = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/account/update_profile_colors">Twitter Documentation for [update_profile_colors]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/account/update_profile_colors}{Twitter Documentation for [update\_profile\_colors]}
* \endlatexonly
*/
TwitterRequest* update_profile_colors_request( str_t profile_background_color = DEF_STR, 
										str_t profile_text_color = DEF_STR, 
										str_t profile_link_color = DEF_STR, 
										str_t profile_sidebar_fill_color = DEF_STR, 
										str_t profile_sidebar_border_color = DEF_STR, 
										bool skip_status = true, 
										bool include_entities = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/blocks/list">Twitter Documentation for [get_blocks_list]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/blocks/list}{Twitter Documentation for [get\_blocks\_list]}
* \endlatexonly
*/
TwitterRequest* get_blocks_list_request( cur_id_t cursor = DEF_STR, 
										bool skip_status = true, 
										bool include_entities = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/blocks/ids">Twitter Documentation for [get_blocks_ids]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/blocks/ids}{Twitter Documentation for [get\_blocks\_ids]}
* \endlatexonly
*/
TwitterRequest* get_blocks_ids_request( cur_id_t cursor = DEF_STR, 
										bool stringify_ids = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/blocks/create">Twitter Documentation for [create_blocks]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/blocks/create}{Twitter Documentation for [create\_blocks]}
* \endlatexonly
*/
TwitterRequest* create_blocks_request( usr_name_t screen_name, 
										bool include_entities = false, 
										bool skip_status = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/blocks/create">Twitter Documentation for [create_blocks_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/blocks/create}{Twitter Documentation for [create\_blocks\_by\_id]}
* \endlatexonly
*/
TwitterRequest* create_blocks_by_id_request( usr_id_t user_id, 
										bool include_entities = false, 
										bool skip_status = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/blocks/destroy">Twitter Documentation for [destroy_blocks]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/blocks/destroy}{Twitter Documentation for [destroy\_blocks]}
* \endlatexonly
*/
TwitterRequest* destroy_blocks_request( usr_name_t screen_name, 
										bool include_entities = false, 
										bool skip_status = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/blocks/destroy">Twitter Documentation for [destroy_blocks_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/blocks/destroy}{Twitter Documentation for [destroy\_blocks\_by\_id]}
* \endlatexonly
*/
TwitterRequest* destroy_blocks_by_id_request( usr_id_t user_id, 
										bool include_entities = false, 
										bool skip_status = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/users/lookup">Twitter Documentation for [lookup_user_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/users/lookup}{Twitter Documentation for [lookup\_user\_by\_id]}
* \endlatexonly
*/
/*
You SHOULD pass user ids or screen names in a "comma,sepa,rated,string"
*/
TwitterRequest* lookup_user_by_id_request( usr_id_t user_id, 
										bool include_entities = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/users/lookup">Twitter Documentation for [lookup_user_by_screen_name]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/users/lookup}{Twitter Documentation for [lookup\_user\_by\_screen\_name]}
* \endlatexonly
*/
/*
You SHOULD pass user ids or screen names in a "comma,sepa,rated,string"
*/
TwitterRequest* lookup_user_by_screen_name_request( usr_name_t screen_name, 
										bool include_entities = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/users/show">Twitter Documentation for [show_user_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/users/show}{Twitter Documentation for [show\_user\_by\_id]}
* \endlatexonly
*/
TwitterRequest* show_user_by_id_request( usr_id_t user_id, 
										bool include_entities = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/users/show">Twitter Documentation for [show_user]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/users/show}{Twitter Documentation for [show\_user]}
* \endlatexonly
*/
TwitterRequest* show_user_request( usr_name_t screen_name, 
										bool include_entities = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/users/search">Twitter Documentation for [search_user]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/users/search}{Twitter Documentation for [search\_user]}
* \endlatexonly
*/
TwitterRequest* search_user_request( str_t q, 
										int count = DEF_NUM, 
										int page = DEF_NUM, 
										bool include_entities = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/users/contributees">Twitter Documentation for [user_contributees_by_user_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/users/contributees}{Twitter Documentation for [user\_contributees\_by\_user\_id]}
* \endlatexonly
*/
TwitterRequest* user_contributees_by_user_id_request( usr_id_t user_id, 
										bool include_entities = true, 
										bool skip_status = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/users/contributees">Twitter Documentation for [user_contributees_by_screen_name]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/users/contributees}{Twitter Documentation for [user\_contributees\_by\_screen\_name]}
* \endlatexonly
*/
TwitterRequest* user_contributees_by_screen_name_request( usr_name_t screen_name, 
										bool include_entities = true, 
										bool skip_status = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/users/contributors">Twitter Documentation for [user_contributors_by_user_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/users/contributors}{Twitter Documentation for [user\_contributors\_by\_user\_id]}
* \endlatexonly
*/
TwitterRequest* user_contributors_by_user_id_request( usr_id_t user_id, 
										bool include_entities = true, 
										bool skip_status = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/users/contributors">Twitter Documentation for [user_contributors_by_screen_name]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/users/contributors}{Twitter Documentation for [user\_contributors\_by\_screen\_name]}
* \endlatexonly
*/

TwitterRequest* user_contributors_by_screen_name_request( usr_name_t screen_name, 
										bool include_entities = true, 
										bool skip_status = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/users/suggestions/:slug">Twitter Documentation for [user_suggestions]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/users/suggestions/:slug}{Twitter Documentation for [user\_suggestions]}
* \endlatexonly
*/
TwitterRequest* user_suggestions_request( slug_t slug, 
										lang_t lang = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/users/suggestions">Twitter Documentation for [user_suggestions_alt]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/users/suggestions}{Twitter Documentation for [user\_suggestions\_alt]}
* \endlatexonly
*/
TwitterRequest* user_suggestions_alt_request( lang_t lang = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/users/suggestions/:slug/members">Twitter Documentation for [user_suggestions_members]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/users/suggestions/:slug/members}{Twitter Documentation for [user\_suggestions\_members]}
* \endlatexonly
*/

TwitterRequest* user_suggestions_members_request( slug_t slug );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/favorites/list">Twitter Documentation for [list_favorites]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/favorites/list}{Twitter Documentation for [list\_favorites]}
* \endlatexonly
*/
TwitterRequest* list_favorites_request( usr_id_t user_id = DEF_STR, 
										int count = DEF_NUM, 
										int since_id = DEF_NUM, 
										int max_id = DEF_NUM, 
										bool include_entities = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/favorites/list">Twitter Documentation for [list_favorites_by_screen_name]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/favorites/list}{Twitter Documentation for [list\_favorites\_by\_screen\_name]}
* \endlatexonly
*/
TwitterRequest* list_favorites_by_screen_name_request( usr_name_t screen_name, 
										int count = DEF_NUM, 
										int since_id = DEF_NUM, 
										int max_id = DEF_NUM, 
										bool include_entities = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/favorites/destroy">Twitter Documentation for [destroy_favorite]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/favorites/destroy}{Twitter Documentation for [destroy\_favorite]}
* \endlatexonly
*/
TwitterRequest* destroy_favorite_request( twt_id_t id, 
										bool include_entities = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/favorites/create">Twitter Documentation for [create_favorite]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/favorites/create}{Twitter Documentation for [create\_favorite]}
* \endlatexonly
*/

TwitterRequest* create_favorite_request( twt_id_t id, 
										bool include_entities = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/list">Twitter Documentation for [lists_by_user_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/list}{Twitter Documentation for [lists\_by\_user\_id]}
* \endlatexonly
*/
TwitterRequest* lists_by_user_id_request( usr_id_t user_id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/list">Twitter Documentation for [lists]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/list}{Twitter Documentation for [lists]}
* \endlatexonly
*/
TwitterRequest* lists_request( usr_id_t screen_name );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/statuses">Twitter Documentation for [list_statuses_by_ids]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/statuses}{Twitter Documentation for [list\_statuses\_by\_ids]}
* \endlatexonly
*/
TwitterRequest* list_statuses_by_ids_request( lst_id_t list_id, 
										int count = DEF_NUM, 
										int since_id = DEF_NUM, 
										int max_id = DEF_NUM, 
										bool include_entities = false, 
										bool include_rts = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/statuses">Twitter Documentation for [list_statuses]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/statuses}{Twitter Documentation for [list\_statuses]}
* \endlatexonly
*/
TwitterRequest* list_statuses_request( slug_t slug, 
										usr_id_t owner_screen_name, 
										int count = DEF_NUM, 
										int since_id = DEF_NUM, 
										int max_id = DEF_NUM, 
										bool include_entities = false, 
										bool include_rts = false );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/members/destroy">Twitter Documentation for [destroy_list_member_by_ids]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/members/destroy}{Twitter Documentation for [destroy\_list\_member\_by\_ids]}
* \endlatexonly
*/
TwitterRequest* destroy_list_member_by_ids_request( lst_id_t list_id, 
										usr_id_t user_id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/members/destroy">Twitter Documentation for [destroy_list_member]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/members/destroy}{Twitter Documentation for [destroy\_list\_member]}
* \endlatexonly
*/
TwitterRequest* destroy_list_member_request( slug_t slug, 
										usr_id_t screen_name );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/memberships">Twitter Documentation for [list_membership]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/memberships}{Twitter Documentation for [list\_membership]}
* \endlatexonly
*/
TwitterRequest* list_membership_request( usr_name_t screen_name, 
										cur_id_t cursor = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/memberships">Twitter Documentation for [list_membership_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/memberships}{Twitter Documentation for [list\_membership\_by\_id]}
* \endlatexonly
*/
TwitterRequest* list_membership_by_id_request( usr_id_t user_id, 
										cur_id_t cursor = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/subscribers">Twitter Documentation for [list_suscribers]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/subscribers}{Twitter Documentation for [list\_suscribers]}
* \endlatexonly
*/
TwitterRequest* list_suscribers_request( slug_t slug, 
										usr_name_t screen_name, 
										cur_id_t cursor, 
										bool include_entities = false, 
										bool skip_status = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/subscribers">Twitter Documentation for [list_suscribers_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/subscribers}{Twitter Documentation for [list\_suscribers\_by\_id]}
* \endlatexonly
*/
TwitterRequest* list_suscribers_by_id_request( lst_id_t list_id, 
										cur_id_t cursor, 
										bool include_entities = false, 
										bool skip_status = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/subscribers/create">Twitter Documentation for [subscribe_to_list]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/subscribers/create}{Twitter Documentation for [subscribe\_to\_list]}
* \endlatexonly
*/
TwitterRequest* subscribe_to_list_request( lst_id_t list_id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/subscribers/create">Twitter Documentation for [subscribe_to_list]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/subscribers/create}{Twitter Documentation for [subscribe\_to\_list]}
* \endlatexonly
*/
TwitterRequest* subscribe_to_list_request( slug_t slug, 
										usr_name_t owner_screen_name );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/subscribers/show">Twitter Documentation for [show_user_is_suscriber_by_ids]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/subscribers/show}{Twitter Documentation for [show\_user\_is\_suscriber\_by\_ids]}
* \endlatexonly
*/
TwitterRequest* show_user_is_suscriber_by_ids_request( usr_id_t user_id, 
										lst_id_t list_id, 
										bool include_entities = false, 
										bool skip_status = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/subscribers/show">Twitter Documentation for [show_user_is_suscriber]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/subscribers/show}{Twitter Documentation for [show\_user\_is\_suscriber]}
* \endlatexonly
*/
TwitterRequest* show_user_is_suscriber_request( usr_name_t screen_name, 
										lst_id_t slug, 
										usr_name_t owner_screen_name, 
										bool include_entities = false, 
										bool skip_status = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/subscribers/destroy">Twitter Documentation for [unsubscribe_from_list]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/subscribers/destroy}{Twitter Documentation for [unsubscribe\_from\_list]}
* \endlatexonly
*/
TwitterRequest* unsubscribe_from_list_request( lst_id_t list_id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/subscribers/destroy">Twitter Documentation for [unsubscribe_from_list]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/subscribers/destroy}{Twitter Documentation for [unsubscribe\_from\_list]}
* \endlatexonly
*/
TwitterRequest* unsubscribe_from_list_request( slug_t slug, 
										usr_name_t owner_screen_name );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/members/create_all">Twitter Documentation for [subscribe_to_list_multi_by_ids]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/members/create_all}{Twitter Documentation for [subscribe\_to\_list\_multi\_by\_ids]}
* \endlatexonly
*/
/*
You SHOULD pass user ids or screen names in a "comma,sepa,rated,string"
*/
TwitterRequest* subscribe_to_list_multi_by_ids_request( lst_id_t list_id, 
										usr_id_t user_id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/members/create_all">Twitter Documentation for [subscribe_to_list_multi]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/members/create_all}{Twitter Documentation for [subscribe\_to\_list\_multi]}
* \endlatexonly
*/
/*
You SHOULD pass user ids or screen names in a "comma,sepa,rated,string"
*/
TwitterRequest* subscribe_to_list_multi_request( slug_t slug, 
										usr_name_t owner_screen_name, 
										usr_name_t screen_name );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/members/show">Twitter Documentation for [show_user_is_member_by_ids]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/members/show}{Twitter Documentation for [show\_user\_is\_member\_by\_ids]}
* \endlatexonly
*/
TwitterRequest* show_user_is_member_by_ids_request( lst_id_t list_id, 
										usr_id_t user_id, 
										bool include_entities = false, 
										bool skip_status = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/members/show">Twitter Documentation for [show_user_is_member]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/members/show}{Twitter Documentation for [show\_user\_is\_member]}
* \endlatexonly
*/
TwitterRequest* show_user_is_member_request( slug_t slug, 
										usr_name_t owner_screen_name, 
										usr_name_t screen_name, 
										bool include_entities = false, 
										bool skip_status = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/members">Twitter Documentation for [list_members_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/members}{Twitter Documentation for [list\_members\_by\_id]}
* \endlatexonly
*/
TwitterRequest* list_members_by_id_request( lst_id_t list_id, 
										cur_id_t cursor = DEF_STR, 
										bool include_entities = false, 
										bool skip_status = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/members">Twitter Documentation for [list_members]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/members}{Twitter Documentation for [list\_members]}
* \endlatexonly
*/
TwitterRequest* list_members_request( slug_t slug, 
										usr_name_t owner_screen_name, 
										cur_id_t cursor, 
										bool include_entities = false, 
										bool skip_status = true );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/members/create">Twitter Documentation for [join_list]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/members/create}{Twitter Documentation for [join\_list]}
* \endlatexonly
*/
TwitterRequest* join_list_request( usr_id_t user_id, 
										lst_id_t list_id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/members/create">Twitter Documentation for [join_list]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/members/create}{Twitter Documentation for [join\_list]}
* \endlatexonly
*/
TwitterRequest* join_list_request( usr_name_t screen_name, 
										slug_t slug, 
										usr_name_t owner_screen_name );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/destroy">Twitter Documentation for [part_from_list]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/destroy}{Twitter Documentation for [part\_from\_list]}
* \endlatexonly
*/
TwitterRequest* part_from_list_request( lst_id_t list_id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/update">Twitter Documentation for [update_list_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/update}{Twitter Documentation for [update\_list\_by\_id]}
* \endlatexonly
*/
TwitterRequest* update_list_by_id_request( lst_id_t list_id, 
										str_t name = DEF_STR, 
										str_t description = "", 
										str_t mode = "public" );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/update">Twitter Documentation for [update_list]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/update}{Twitter Documentation for [update\_list]}
* \endlatexonly
*/
TwitterRequest* update_list_request( slug_t slug, 
										usr_name_t owner_screen_name, 
										str_t name = DEF_STR, 
										str_t description = "", 
										str_t mode = "public" );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/create">Twitter Documentation for [create_list]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/create}{Twitter Documentation for [create\_list]}
* \endlatexonly
*/
TwitterRequest* create_list_request( str_t name, 
										str_t description = "", 
										bool mode = "public" );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/show">Twitter Documentation for [show_list]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/show}{Twitter Documentation for [show\_list]}
* \endlatexonly
*/
TwitterRequest* show_list_request( lst_id_t list_id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/show">Twitter Documentation for [show_list]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/show}{Twitter Documentation for [show\_list]}
* \endlatexonly
*/
TwitterRequest* show_list_request( slug_t slug, 
										usr_name_t owner_screen_name );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/subscriptions">Twitter Documentation for [lists_subscription_by_id]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/subscriptions}{Twitter Documentation for [lists\_subscription\_by\_id]}
* \endlatexonly
*/
TwitterRequest* lists_subscription_by_id_request( usr_id_t user_id, 
										int count = DEF_NUM, 
										cur_id_t cursor = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/lists/subscriptions">Twitter Documentation for [lists_subscription]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/lists/subscriptions}{Twitter Documentation for [lists\_subscription]}
* \endlatexonly
*/
TwitterRequest* lists_subscription_request( usr_name_t screen_name, 
										int count = DEF_NUM, 
										cur_id_t cursor = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/members/destroy_all">Twitter Documentation for [expulse_from_list_by_ids]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/members/destroy_all}{Twitter Documentation for [expulse\_from\_list\_by\_ids]}
* \endlatexonly
*/
/*
You SHOULD pass user ids or screen names in a "comma,sepa,rated,string"
*/
TwitterRequest* expulse_from_list_by_ids_request( lst_id_t list_id, 
										usr_id_t user_id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/lists/members/destroy_all">Twitter Documentation for [expulse_from_list]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/lists/members/destroy_all}{Twitter Documentation for [expulse\_from\_list]}
* \endlatexonly
*/
/*
You SHOULD pass user ids or screen names in a "comma,sepa,rated,string"
*/

TwitterRequest* expulse_from_list_request( slug_t slug, 
										usr_name_t owner_screen_name, 
										usr_name_t screen_name );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/saved_searches/list">Twitter Documentation for [get_saved_searches]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/saved_searches/list}{Twitter Documentation for [get\_saved\_searches]}
* \endlatexonly
*/
TwitterRequest* get_saved_searches_request(  );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/saved_searches/show/:id">Twitter Documentation for [show_saved_search]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/saved_searches/show/:id}{Twitter Documentation for [show\_saved\_search]}
* \endlatexonly
*/
TwitterRequest* show_saved_search_request( sch_id_t id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/saved_searches/create">Twitter Documentation for [search]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/saved_searches/create}{Twitter Documentation for [search]}
* \endlatexonly
*/
TwitterRequest* search_request( str_t query );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/saved_searches/destroy/:id">Twitter Documentation for [destroy_saved_search]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/saved_searches/destroy/:id}{Twitter Documentation for [destroy\_saved\_search]}
* \endlatexonly
*/



TwitterRequest* destroy_saved_search_request( sch_id_t id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/trends/place">Twitter Documentation for [trends_place]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/trends/place}{Twitter Documentation for [trends\_place]}
* \endlatexonly
*/
TwitterRequest* trends_place_request( int id, 
										str_t exclude = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/trends/available">Twitter Documentation for [available_trends]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/trends/available}{Twitter Documentation for [available\_trends]}
* \endlatexonly
*/
TwitterRequest* available_trends_request(  );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/trends/closest">Twitter Documentation for [closest_trend]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/trends/closest}{Twitter Documentation for [closest\_trend]}
* \endlatexonly
*/


TwitterRequest* closest_trend_request( float Lat, 
										float Long );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/report_spam">Twitter Documentation for [report_spam]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/report_spam}{Twitter Documentation for [report\_spam]}
* \endlatexonly
*/

TwitterRequest* report_spam_request( usr_id_t user_id );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/application/rate_limit_status">Twitter Documentation for [rate_limit_status]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/application/rate_limit_status}{Twitter Documentation for [rate\_limit\_status]}
* \endlatexonly
*/
/*
You SHOULD pass ressources names in a "comma,sepa,rated,string"
*/
TwitterRequest* rate_limit_status_request( str_t ressources );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/help/languages">Twitter Documentation for [help_languages]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/help/languages}{Twitter Documentation for [help\_languages]}
* \endlatexonly
*/
TwitterRequest* help_languages_request(  );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/help/privacy">Twitter Documentation for [help_privacy]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/help/privacy}{Twitter Documentation for [help\_privacy]}
* \endlatexonly
*/
TwitterRequest* help_privacy_request(  );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/help/tos">Twitter Documentation for [help_TOS]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/help/tos}{Twitter Documentation for [help\_TOS]}
* \endlatexonly
*/
TwitterRequest* help_TOS_request(  );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/application/rate_limit_status">Twitter Documentation for [application_rate_limit_status]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/application/rate_limit_status}{Twitter Documentation for [application\_rate\_limit\_status]}
* \endlatexonly
*/

TwitterRequest* application_rate_limit_status_request( str_t ressources = DEF_STR );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/get/https://userstream.twitter.com/1.1/user">Twitter Documentation for [user_stream]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/get/https://userstream.twitter.com/1.1/user}{Twitter Documentation for [user\_stream]}
* \endlatexonly
*/
TwitterRequest* user_stream_request( str_t with = DEF_STR, 
										str_t replies = DEF_STR, 
										str_t track = DEF_STR, 
										str_t locations = DEF_STR, 
										bool delimited = false, 
										bool stall_warnings = false );

/* END_PYGEN don't remove this comment (2012/10/27 14:35) */


/* MANUALLY (file uploads) */

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/statuses/update">Twitter Documentation for [update_status]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/statuses/update_with_media}{Twitter Documentation for [update\_status_with_media]}
* \endlatexonly
*/
TwitterRequest* update_status_with_media_request( 
										str_t status, 
										str_t media_path,
										str_t in_reply_to_status_id = DEF_STR,
										bool possibly_sensitive = false, 
										str_t place_id = DEF_STR, 
										bool display_coordinates = false, 
										bool trim_user = false, 
										float lat = DEF_NUM, 
										float lon = DEF_NUM );

/**
* \htmlonly 
* <a target="_blank"href="http://dev.twitter.com/docs/api/1.1/post/statuses/update">Twitter Documentation for [update_status]<a>
* \endhtmlonly
* \latexonly 
* \href{http://dev.twitter.com/docs/api/1.1/post/statuses/update_with_media}{Twitter Documentation for [update\_status_with_media]}
* \endlatexonly
*/
TwitterRequest* update_status_with_media_request( 
										str_t status, 
										std::list<std::string> media_paths,
										str_t in_reply_to_status_id = DEF_STR,
										bool possibly_sensitive = false, 
										str_t place_id = DEF_STR, 
										bool display_coordinates = false, 
										bool trim_user = false, 
										float lat = DEF_NUM, 
										float lon = DEF_NUM );


	protected:

		GenericFactory* _requests_factory;

		TwitterRequest* _next_request;


	private:

		TwitterRequest* _update_status_with_media_request( str_t status, str_t in_reply_to_status_id, bool possibly_sensitive,  str_t place_id,  bool display_coordinates,  bool trim_user,  float lat,  float lon );

	};

#endif /* H_REQUEST_CREATOR_H */