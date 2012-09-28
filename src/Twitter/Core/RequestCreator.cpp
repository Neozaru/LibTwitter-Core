#include "RequestCreator.h"

#include "TwitterRequest.h"

#include "args_macros.h"
#include "Utils.h"

RequestCreator::RequestCreator( GenericFactory* factory ) : _next_request(NULL) {
	_requests_factory = factory;
}

RequestCreator::~RequestCreator() {

}


TwitterRequest* RequestCreator::__make_a_request( const std::string& url ) {
	
	if ( _next_request == NULL ) {

		return _requests_factory->create_request(url);
	}
	else {

		TwitterRequest* next = _next_request;
		next->set_URL(url);

		/* Doesn't delete the pointed object, only the "_next_request" value */
		_next_request = NULL;

		return next;

	}
}


void RequestCreator::set_next_request( TwitterRequest* req ) {
	_next_request = req;	
}

/********************/
/* REQUESTS METHODS */
/********************/

/* REC_ARGS_X : Convert X arguments to String, and put them in a std::map */
/* 				"<var_name>" => "<var_value_in_string>" */

/*
TwitterRequest* RequestCreator::update_status_request( const std::string& status, int in_reply_to, bool display_coordinates,
						 					bool trim_user ) {

	PUT_VAR_IN_URL( TwitterConsts::Tweets::UPDATE, in_reply_to );
	TwitterRequest* req = __make_a_request( TwitterConsts::Tweets::UPDATE );
	req->set_POST_data( REC_ARGS_4( status, in_reply_to, display_coordinates, trim_user ) );

	return req;
}
*/
/*
TwitterRequest* RequestCreator::verify_credentials_request() {


	TwitterRequest* req = __make_a_request( TwitterConsts::Users::VERIFY_CREDENTIALS );

	return req;

}


TwitterRequest* RequestCreator::get_settings_request() {

	TwitterRequest* req = __make_a_request( TwitterConsts::Settings::GET_SETTINGS );

	return req;
}
*/

TwitterRequest* RequestCreator::stream_user_request( std::string with, std::string track ) {

	TwitterRequest* req = __make_a_request( TwitterConsts::Streaming::STREAM_USER );
	req->set_POST_data( REC_ARGS_2( with, track ) );

	return req;

}

/* BEGIN_PYGEN don't remove this comment (2012/9/28 12:15) */
TwitterRequest* RequestCreator::mentions_timeline_request( int count, uid_t since_id, int max_id, bool trim_user, bool contributor_details, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::MENTIONS_TIMELINE );
	req->set_GET_data( REC_ARGS_6( count, since_id, max_id, trim_user, contributor_details, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::user_timeline_request( int user_id, const std::string& screen_name, int count, uid_t since_id, int max_id, bool trim_user, bool exclude_replies, bool contributor_details, bool include_rts ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::USER_TIMELINE );
	req->set_GET_data( REC_ARGS_9( user_id, screen_name, count, since_id, max_id, trim_user, exclude_replies, contributor_details, include_rts ) );
	return req;
}

TwitterRequest* RequestCreator::home_timeline_request( int count, uid_t since_id, int max_id, bool trim_user, bool exclude_replies, bool contributor_details, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::HOME_TIMELINE );
	req->set_GET_data( REC_ARGS_7( count, since_id, max_id, trim_user, exclude_replies, contributor_details, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::retweets_request( uid_t id, int count, bool trim_user ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::STATUSES::RETWEETS, id )
	 );
	req->set_GET_data( REC_ARGS_2( count, trim_user ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_status_request( uid_t id, bool trim_user ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::STATUSES::DESTROY, id )
	 );
	req->set_POST_data( REC_ARGS_1( trim_user ) );
	return req;
}

TwitterRequest* RequestCreator::update_status_request( const std::string& status, const std::string& in_reply_to_status_id, const std::string& place_id, bool display_coordinates, bool trim_user, float lat, float lon ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::UPDATE );
	req->set_POST_data( REC_ARGS_7( status, in_reply_to_status_id, place_id, display_coordinates, trim_user, lat, lon ) );
	return req;
}

TwitterRequest* RequestCreator::retweet_request( uid_t id, bool trim_user ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::STATUSES::RETWEET, id )
	 );
	req->set_POST_data( REC_ARGS_1( trim_user ) );
	return req;
}

TwitterRequest* RequestCreator::oembed_status_request( uid_t id, const std::string& url, int maxwidth, bool hide_media, bool hide_thread, bool omit_script, const std::string& align, const std::string& related, const std::string& lang ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::OEMBED );
	req->set_GET_data( REC_ARGS_9( id, url, maxwidth, hide_media, hide_thread, omit_script, align, related, lang ) );
	return req;
}

TwitterRequest* RequestCreator::search_tweets_request( const std::string& q, const std::string& locale, const std::string& result_type, int count, const std::string& until, uid_t since_id, const std::string& max_id, bool include_entities, const std::string& callback ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::SEARCH::TWEETS );
	req->set_GET_data( REC_ARGS_9( q, locale, result_type, count, until, since_id, max_id, include_entities, callback ) );
	return req;
}

TwitterRequest* RequestCreator::sent_direct_messages_request( int count, int page, uid_t since_id, const std::string& max_id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::DIRECT_MESSAGES::SENT );
	req->set_GET_data( REC_ARGS_5( count, page, since_id, max_id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::show_direct_messages_request( uid_t id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::DIRECT_MESSAGES::SHOW );
	req->set_GET_data( REC_ARGS_1( id ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_direct_messages_request( uid_t id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::DIRECT_MESSAGES::DESTROY );
	req->set_POST_data( REC_ARGS_2( id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::new_direct_message_by_user_id_request( const std::string& user_id, const std::string& text ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::DIRECT_MESSAGES::NEW );
	req->set_POST_data( REC_ARGS_2( user_id, text ) );
	return req;
}

TwitterRequest* RequestCreator::new_direct_message_by_screen_name_request( const std::string& screen_name, const std::string& text ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::DIRECT_MESSAGES::NEW );
	req->set_POST_data( REC_ARGS_2( screen_name, text ) );
	return req;
}

TwitterRequest* RequestCreator::friends_ids_request( uid_t user_id, bool stringify_ids ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDS::IDS );
	req->set_GET_data( REC_ARGS_2( user_id, stringify_ids ) );
	return req;
}

TwitterRequest* RequestCreator::friends_ids_request( const std::string& screen_name, bool stringify_ids ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDS::IDS );
	req->set_GET_data( REC_ARGS_2( screen_name, stringify_ids ) );
	return req;
}

TwitterRequest* RequestCreator::followers_ids_request( uid_t user_id, bool stringify_ids ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FOLLOWERS::IDS );
	req->set_GET_data( REC_ARGS_2( user_id, stringify_ids ) );
	return req;
}

TwitterRequest* RequestCreator::followers_ids_request( const std::string& screen_name, bool stringify_ids ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FOLLOWERS::IDS );
	req->set_GET_data( REC_ARGS_2( screen_name, stringify_ids ) );
	return req;
}

TwitterRequest* RequestCreator::lookup_friendship_by_names_request( const std::string& screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::LOOKUP );
	req->set_GET_data( REC_ARGS_1( screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::lookup_friendship_by_ids_request( const std::string& user_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::LOOKUP );
	req->set_GET_data( REC_ARGS_1( user_id ) );
	return req;
}

TwitterRequest* RequestCreator::incoming_friendships_request( bool stringify_ids ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::INCOMING );
	req->set_GET_data( REC_ARGS_1( stringify_ids ) );
	return req;
}

TwitterRequest* RequestCreator::outgoing_friendships_request( bool stringify_ids ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::OUTGOING );
	req->set_GET_data( REC_ARGS_1( stringify_ids ) );
	return req;
}

TwitterRequest* RequestCreator::create_friendship_request( const std::string& screen_name, bool follow ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::CREATE );
	req->set_POST_data( REC_ARGS_2( screen_name, follow ) );
	return req;
}

TwitterRequest* RequestCreator::create_friendship_request( uid_t user_id, bool follow ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::CREATE );
	req->set_POST_data( REC_ARGS_2( user_id, follow ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_friendship_request( const std::string& screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::DESTROY );
	req->set_POST_data( REC_ARGS_1( screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_friendship_request( uid_t user_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::DESTROY );
	req->set_POST_data( REC_ARGS_1( user_id ) );
	return req;
}

TwitterRequest* RequestCreator::update_friendship_request( const std::string& screen_name, bool retweets, bool device ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::UPDATE );
	req->set_POST_data( REC_ARGS_3( screen_name, retweets, device ) );
	return req;
}

TwitterRequest* RequestCreator::update_friendship_request( uid_t user_id, bool retweets, bool device ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::UPDATE );
	req->set_POST_data( REC_ARGS_3( user_id, retweets, device ) );
	return req;
}

TwitterRequest* RequestCreator::show_friendship_request( uid_t source_id, uid_t target_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::SHOW );
	req->set_GET_data( REC_ARGS_2( source_id, target_id ) );
	return req;
}

TwitterRequest* RequestCreator::show_friendship_request( const std::string& source_screen_name, const std::string& target_screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::SHOW );
	req->set_GET_data( REC_ARGS_2( source_screen_name, target_screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::verify_credentials_request( bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::ACCOUNT::VERIFY_CREDENTIALS );
	req->set_GET_data( REC_ARGS_2( include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::update_delivery_device_request( const std::string& device, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::ACCOUNT::UPDATE_DELIVERY_DEVICE );
	req->set_POST_data( REC_ARGS_2( device, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::update_profile_background_image_request( bool use, const std::string& image, bool tile, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::ACCOUNT::UPDATE_PROFILE_BACKGROUND_IMAGE );
	req->set_POST_data( REC_ARGS_4( use, image, tile, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::update_profile_colors_request( const std::string& profile_background_color, const std::string& profile_text_color, const std::string& profile_link_color, const std::string& profile_sidebar_fill_color, const std::string& profile_sidebar_border_color, bool skip_status, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::ACCOUNT::UPDATE_PROFILE_COLORS );
	req->set_POST_data( REC_ARGS_7( profile_background_color, profile_text_color, profile_link_color, profile_sidebar_fill_color, profile_sidebar_border_color, skip_status, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::get_blocks_list_request( cid_t cursor, bool skip_status, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::BLOCKS::LIST );
	req->set_GET_data( REC_ARGS_3( cursor, skip_status, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::get_blocks_ids_request( cid_t cursor, bool stringify_ids ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::BLOCKS::IDS );
	req->set_GET_data( REC_ARGS_2( cursor, stringify_ids ) );
	return req;
}

TwitterRequest* RequestCreator::create_blocks_by_screen_name_request( const std::string& screen_name, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::BLOCKS::CREATE );
	req->set_POST_data( REC_ARGS_3( screen_name, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::create_blocks_by_id_request( uid_t user_id, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::BLOCKS::CREATE );
	req->set_POST_data( REC_ARGS_3( user_id, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_blocks_by_screen_name_request( const std::string& screen_name, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::BLOCKS::DESTROY );
	req->set_POST_data( REC_ARGS_3( screen_name, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_blocks_by_id_request( uid_t user_id, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::BLOCKS::DESTROY );
	req->set_POST_data( REC_ARGS_3( user_id, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::lookup_user_by_id_request( const std::string& user_id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::LOOKUP );
	req->set_GET_data( REC_ARGS_2( user_id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::lookup_user_by_screen_name_request( const std::string& screen_name, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::LOOKUP );
	req->set_GET_data( REC_ARGS_2( screen_name, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::show_user_by_id_request( const std::string& user_id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::SHOW );
	req->set_GET_data( REC_ARGS_2( user_id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::show_user_by_screen_name_request( const std::string& screen_name, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::SHOW );
	req->set_GET_data( REC_ARGS_2( screen_name, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::search_user_request( const std::string& q, int count, int page, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::SEARCH );
	req->set_GET_data( REC_ARGS_4( q, count, page, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::user_contributees_by_user_id_request( uid_t user_id, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::CONTRIBUTEES );
	req->set_GET_data( REC_ARGS_3( user_id, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::user_contributees_by_screen_name_request( const std::string& screen_name, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::CONTRIBUTEES );
	req->set_GET_data( REC_ARGS_3( screen_name, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::user_contributors_by_user_id_request( uid_t user_id, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::CONTRIBUTORS );
	req->set_GET_data( REC_ARGS_3( user_id, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::user_contributors_by_screen_name_request( const std::string& screen_name, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::CONTRIBUTORS );
	req->set_GET_data( REC_ARGS_3( screen_name, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::user_suggestions_request( const std::string& slug, const std::string& lang ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::USERS::SUGGESTIONS, slug )
	 );
	req->set_GET_data( REC_ARGS_1( lang ) );
	return req;
}

TwitterRequest* RequestCreator::user_suggestions_alt_request( const std::string& lang ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::SUGGESTIONS );
	req->set_GET_data( REC_ARGS_1( lang ) );
	return req;
}

TwitterRequest* RequestCreator::user_suggestions_members_request( const std::string& slug ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::USERS::SUGGESTIONS, slug )
	 );

	return req;
}

TwitterRequest* RequestCreator::list_favorites_request( uid_t user_id, int count, int since_id, int max_id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FAVORITES::LIST );
	req->set_GET_data( REC_ARGS_5( user_id, count, since_id, max_id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::list_favorites_by_screen_name_request( const std::string& screen_name, int count, int since_id, int max_id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FAVORITES::LIST );
	req->set_GET_data( REC_ARGS_5( screen_name, count, since_id, max_id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_favorite_request( tid_t id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FAVORITES::DESTROY );
	req->set_POST_data( REC_ARGS_2( id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::create_favorite_request( tid_t id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FAVORITES::CREATE );
	req->set_POST_data( REC_ARGS_2( id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::lists_by_user_id_request( uid_t user_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::LIST );
	req->set_GET_data( REC_ARGS_1( user_id ) );
	return req;
}

TwitterRequest* RequestCreator::lists_by_screen_name_request( uid_t screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::LIST );
	req->set_GET_data( REC_ARGS_1( screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::list_statuses_by_ids_request( lid_t list_id, uid_t owner_id, int count, int since_id, int max_id, bool include_entities, bool include_rts ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::STATUSES );
	req->set_GET_data( REC_ARGS_7( list_id, owner_id, count, since_id, max_id, include_entities, include_rts ) );
	return req;
}

TwitterRequest* RequestCreator::list_statuses_by_names_request( lid_t slug, uid_t owner_screen_name, int count, int since_id, int max_id, bool include_entities, bool include_rts ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::STATUSES );
	req->set_GET_data( REC_ARGS_7( slug, owner_screen_name, count, since_id, max_id, include_entities, include_rts ) );
	return req;
}

/* END_PYGEN don't remove this comment (2012/9/28 12:15) */

