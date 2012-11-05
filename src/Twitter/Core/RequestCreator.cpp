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


/* BEGIN_PYGEN don't remove this comment (2012/10/27 14:35) */
TwitterRequest* RequestCreator::mentions_timeline_request( int count, usr_id_t since_id, int max_id, bool trim_user, bool contributor_details, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::MENTIONS_TIMELINE );
	req->set_GET_data( REC_ARGS_6( count, since_id, max_id, trim_user, contributor_details, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::user_timeline_by_id_request( usr_id_t user_id, int count, twt_id_t since_id, twt_id_t max_id, bool trim_user, bool exclude_replies, bool contributor_details, bool include_rts ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::USER_TIMELINE );
	req->set_GET_data( REC_ARGS_8( user_id, count, since_id, max_id, trim_user, exclude_replies, contributor_details, include_rts ) );
	return req;
}

TwitterRequest* RequestCreator::user_timeline_request( usr_name_t screen_name, int count, twt_id_t since_id, twt_id_t max_id, bool trim_user, bool exclude_replies, bool contributor_details, bool include_rts ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::USER_TIMELINE );
	req->set_GET_data( REC_ARGS_8( screen_name, count, since_id, max_id, trim_user, exclude_replies, contributor_details, include_rts ) );
	return req;
}

TwitterRequest* RequestCreator::home_timeline_request( int count, usr_id_t since_id, int max_id, bool trim_user, bool exclude_replies, bool contributor_details, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::HOME_TIMELINE );
	req->set_GET_data( REC_ARGS_7( count, since_id, max_id, trim_user, exclude_replies, contributor_details, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::get_retweets_request( twt_id_t id, int count, bool trim_user ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::STATUSES::RETWEETS, id )
	 );
	req->set_GET_data( REC_ARGS_2( count, trim_user ) );
	return req;
}

TwitterRequest* RequestCreator::show_status_request( twt_id_t id, bool include_my_retweet, bool trim_user, bool include_entities ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::STATUSES::SHOW, id )
	 );
	req->set_GET_data( REC_ARGS_3( include_my_retweet, trim_user, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_status_request( twt_id_t id, bool trim_user ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::STATUSES::DESTROY, id )
	 );
	req->set_POST_data( REC_ARGS_1( trim_user ) );
	return req;
}

TwitterRequest* RequestCreator::update_status_request( str_t status, str_t in_reply_to_status_id, str_t place_id, bool display_coordinates, bool trim_user, float lat, float lon ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::UPDATE );
	req->set_POST_data( REC_ARGS_7( status, in_reply_to_status_id, place_id, display_coordinates, trim_user, lat, lon ) );
	return req;
}

TwitterRequest* RequestCreator::retweet_request( twt_id_t id, bool trim_user ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::STATUSES::RETWEET, id )
	 );
	req->set_POST_data( REC_ARGS_1( trim_user ) );
	return req;
}

TwitterRequest* RequestCreator::oembed_status_request( twt_id_t id, str_t url, int maxwidth, bool hide_media, bool hide_thread, bool omit_script, str_t align, str_t related, lang_t lang ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::OEMBED );
	req->set_GET_data( REC_ARGS_9( id, url, maxwidth, hide_media, hide_thread, omit_script, align, related, lang ) );
	return req;
}

TwitterRequest* RequestCreator::search_tweets_request( str_t q, str_t locale, str_t result_type, int count, str_t until, twt_id_t since_id, twt_id_t max_id, bool include_entities, str_t callback ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::SEARCH::TWEETS );
	req->set_GET_data( REC_ARGS_9( q, locale, result_type, count, until, since_id, max_id, include_entities, callback ) );
	return req;
}

TwitterRequest* RequestCreator::sent_direct_messages_request( int count, int page, usr_id_t since_id, str_t max_id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::DIRECT_MESSAGES::SENT );
	req->set_GET_data( REC_ARGS_5( count, page, since_id, max_id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::show_direct_messages_request( msg_id_t id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::DIRECT_MESSAGES::SHOW );
	req->set_GET_data( REC_ARGS_1( id ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_direct_messages_request( msg_id_t id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::DIRECT_MESSAGES::DESTROY );
	req->set_POST_data( REC_ARGS_2( id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::new_direct_message_by_id_request( usr_id_t user_id, str_t text ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::DIRECT_MESSAGES::NEW );
	req->set_POST_data( REC_ARGS_2( user_id, text ) );
	return req;
}

TwitterRequest* RequestCreator::new_direct_message_request( usr_name_t screen_name, str_t text ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::DIRECT_MESSAGES::NEW );
	req->set_POST_data( REC_ARGS_2( screen_name, text ) );
	return req;
}

TwitterRequest* RequestCreator::friends_ids_by_id_request( usr_id_t user_id, bool stringify_ids, cur_id_t cursor ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDS::IDS );
	req->set_GET_data( REC_ARGS_3( user_id, stringify_ids, cursor ) );
	return req;
}

TwitterRequest* RequestCreator::friends_ids_request( usr_name_t screen_name, bool stringify_ids, cur_id_t cursor ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDS::IDS );
	req->set_GET_data( REC_ARGS_3( screen_name, stringify_ids, cursor ) );
	return req;
}

TwitterRequest* RequestCreator::followers_ids_by_id_request( usr_id_t user_id, bool stringify_ids, cur_id_t cursor ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FOLLOWERS::IDS );
	req->set_GET_data( REC_ARGS_3( user_id, stringify_ids, cursor ) );
	return req;
}

TwitterRequest* RequestCreator::followers_ids_request( usr_name_t screen_name, bool stringify_ids, cur_id_t cursor ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FOLLOWERS::IDS );
	req->set_GET_data( REC_ARGS_3( screen_name, stringify_ids, cursor ) );
	return req;
}

TwitterRequest* RequestCreator::lookup_friendship_request( usr_name_t screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::LOOKUP );
	req->set_GET_data( REC_ARGS_1( screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::lookup_friendship_by_ids_request( usr_id_t user_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::LOOKUP );
	req->set_GET_data( REC_ARGS_1( user_id ) );
	return req;
}

TwitterRequest* RequestCreator::incoming_friendships_request( bool stringify_ids, cur_id_t cursor ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::INCOMING );
	req->set_GET_data( REC_ARGS_2( stringify_ids, cursor ) );
	return req;
}

TwitterRequest* RequestCreator::outgoing_friendships_request( bool stringify_ids, cur_id_t cursor ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::OUTGOING );
	req->set_GET_data( REC_ARGS_2( stringify_ids, cursor ) );
	return req;
}

TwitterRequest* RequestCreator::create_friendship_request( usr_name_t screen_name, bool follow ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::CREATE );
	req->set_POST_data( REC_ARGS_2( screen_name, follow ) );
	return req;
}

TwitterRequest* RequestCreator::create_friendship_by_id_request( usr_id_t user_id, bool follow ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::CREATE );
	req->set_POST_data( REC_ARGS_2( user_id, follow ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_friendship_request( usr_name_t screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::DESTROY );
	req->set_POST_data( REC_ARGS_1( screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_friendship_by_id_request( usr_id_t user_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::DESTROY );
	req->set_POST_data( REC_ARGS_1( user_id ) );
	return req;
}

TwitterRequest* RequestCreator::update_friendship_request( usr_name_t screen_name, bool retweets, bool device ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::UPDATE );
	req->set_POST_data( REC_ARGS_3( screen_name, retweets, device ) );
	return req;
}

TwitterRequest* RequestCreator::update_friendship_by_id_request( usr_id_t user_id, bool retweets, bool device ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::UPDATE );
	req->set_POST_data( REC_ARGS_3( user_id, retweets, device ) );
	return req;
}

TwitterRequest* RequestCreator::show_friendship_request( usr_name_t source_screen_name, usr_name_t target_screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::SHOW );
	req->set_GET_data( REC_ARGS_2( source_screen_name, target_screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::show_friendship_by_id_request( usr_id_t source_id, usr_id_t target_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FRIENDSHIPS::SHOW );
	req->set_GET_data( REC_ARGS_2( source_id, target_id ) );
	return req;
}

TwitterRequest* RequestCreator::verify_credentials_request( bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::ACCOUNT::VERIFY_CREDENTIALS );
	req->set_GET_data( REC_ARGS_2( include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::set_account_settings_request( bool sleep_time_enabled, int start_sleep_time, int end_sleep_time, lang_t lang, str_t time_zone, int trend_location_woeid ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::ACCOUNT::SETTINGS );
	req->set_POST_data( REC_ARGS_6( sleep_time_enabled, start_sleep_time, end_sleep_time, lang, time_zone, trend_location_woeid ) );
	return req;
}

TwitterRequest* RequestCreator::update_delivery_device_request( str_t device, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::ACCOUNT::UPDATE_DELIVERY_DEVICE );
	req->set_POST_data( REC_ARGS_2( device, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::update_profile_request( str_t name, str_t description, str_t url, bool include_entities, bool skip_status, str_t location ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::ACCOUNT::UPDATE_PROFILE );
	req->set_POST_data( REC_ARGS_6( name, description, url, include_entities, skip_status, location ) );
	return req;
}

TwitterRequest* RequestCreator::update_profile_background_image_request( bool use, str_t image, bool tile, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::ACCOUNT::UPDATE_PROFILE_BACKGROUND_IMAGE );
	req->set_POST_data( REC_ARGS_4( use, image, tile, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::update_profile_colors_request( str_t profile_background_color, str_t profile_text_color, str_t profile_link_color, str_t profile_sidebar_fill_color, str_t profile_sidebar_border_color, bool skip_status, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::ACCOUNT::UPDATE_PROFILE_COLORS );
	req->set_POST_data( REC_ARGS_7( profile_background_color, profile_text_color, profile_link_color, profile_sidebar_fill_color, profile_sidebar_border_color, skip_status, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::get_blocks_list_request( cur_id_t cursor, bool skip_status, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::BLOCKS::LIST );
	req->set_GET_data( REC_ARGS_3( cursor, skip_status, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::get_blocks_ids_request( cur_id_t cursor, bool stringify_ids ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::BLOCKS::IDS );
	req->set_GET_data( REC_ARGS_2( cursor, stringify_ids ) );
	return req;
}

TwitterRequest* RequestCreator::create_blocks_request( usr_name_t screen_name, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::BLOCKS::CREATE );
	req->set_POST_data( REC_ARGS_3( screen_name, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::create_blocks_by_id_request( usr_id_t user_id, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::BLOCKS::CREATE );
	req->set_POST_data( REC_ARGS_3( user_id, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_blocks_request( usr_name_t screen_name, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::BLOCKS::DESTROY );
	req->set_POST_data( REC_ARGS_3( screen_name, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_blocks_by_id_request( usr_id_t user_id, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::BLOCKS::DESTROY );
	req->set_POST_data( REC_ARGS_3( user_id, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::lookup_user_by_id_request( usr_id_t user_id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::LOOKUP );
	req->set_GET_data( REC_ARGS_2( user_id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::lookup_user_by_screen_name_request( usr_name_t screen_name, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::LOOKUP );
	req->set_GET_data( REC_ARGS_2( screen_name, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::show_user_by_id_request( usr_id_t user_id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::SHOW );
	req->set_GET_data( REC_ARGS_2( user_id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::show_user_request( usr_name_t screen_name, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::SHOW );
	req->set_GET_data( REC_ARGS_2( screen_name, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::search_user_request( str_t q, int count, int page, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::SEARCH );
	req->set_GET_data( REC_ARGS_4( q, count, page, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::user_contributees_by_user_id_request( usr_id_t user_id, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::CONTRIBUTEES );
	req->set_GET_data( REC_ARGS_3( user_id, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::user_contributees_by_screen_name_request( usr_name_t screen_name, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::CONTRIBUTEES );
	req->set_GET_data( REC_ARGS_3( screen_name, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::user_contributors_by_user_id_request( usr_id_t user_id, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::CONTRIBUTORS );
	req->set_GET_data( REC_ARGS_3( user_id, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::user_contributors_by_screen_name_request( usr_name_t screen_name, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::CONTRIBUTORS );
	req->set_GET_data( REC_ARGS_3( screen_name, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::user_suggestions_request( slug_t slug, lang_t lang ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::USERS::SUGGESTIONS, slug )
	 );
	req->set_GET_data( REC_ARGS_1( lang ) );
	return req;
}

TwitterRequest* RequestCreator::user_suggestions_alt_request( lang_t lang ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::USERS::SUGGESTIONS );
	req->set_GET_data( REC_ARGS_1( lang ) );
	return req;
}

TwitterRequest* RequestCreator::user_suggestions_members_request( slug_t slug ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::USERS::SUGGESTIONS, slug )
	 );

	return req;
}

TwitterRequest* RequestCreator::list_favorites_request( usr_id_t user_id, int count, int since_id, int max_id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FAVORITES::LIST );
	req->set_GET_data( REC_ARGS_5( user_id, count, since_id, max_id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::list_favorites_by_screen_name_request( usr_name_t screen_name, int count, int since_id, int max_id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FAVORITES::LIST );
	req->set_GET_data( REC_ARGS_5( screen_name, count, since_id, max_id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_favorite_request( twt_id_t id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FAVORITES::DESTROY );
	req->set_POST_data( REC_ARGS_2( id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::create_favorite_request( twt_id_t id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::FAVORITES::CREATE );
	req->set_POST_data( REC_ARGS_2( id, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::lists_by_user_id_request( usr_id_t user_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::LIST );
	req->set_GET_data( REC_ARGS_1( user_id ) );
	return req;
}

TwitterRequest* RequestCreator::lists_request( usr_id_t screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::LIST );
	req->set_GET_data( REC_ARGS_1( screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::list_statuses_by_ids_request( lst_id_t list_id, int count, int since_id, int max_id, bool include_entities, bool include_rts ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::STATUSES );
	req->set_GET_data( REC_ARGS_6( list_id, count, since_id, max_id, include_entities, include_rts ) );
	return req;
}

TwitterRequest* RequestCreator::list_statuses_request( slug_t slug, usr_id_t owner_screen_name, int count, int since_id, int max_id, bool include_entities, bool include_rts ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::STATUSES );
	req->set_GET_data( REC_ARGS_7( slug, owner_screen_name, count, since_id, max_id, include_entities, include_rts ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_list_member_by_ids_request( lst_id_t list_id, usr_id_t user_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::MEMBERS );
	req->set_POST_data( REC_ARGS_2( list_id, user_id ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_list_member_request( slug_t slug, usr_id_t screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::MEMBERS );
	req->set_POST_data( REC_ARGS_2( slug, screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::list_membership_request( usr_name_t screen_name, cur_id_t cursor ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::MEMBERSHIPS );
	req->set_GET_data( REC_ARGS_2( screen_name, cursor ) );
	return req;
}

TwitterRequest* RequestCreator::list_membership_by_id_request( usr_id_t user_id, cur_id_t cursor ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::MEMBERSHIPS );
	req->set_GET_data( REC_ARGS_2( user_id, cursor ) );
	return req;
}

TwitterRequest* RequestCreator::list_suscribers_request( slug_t slug, usr_name_t screen_name, cur_id_t cursor, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::SUBSCRIBERS );
	req->set_GET_data( REC_ARGS_5( slug, screen_name, cursor, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::list_suscribers_by_id_request( lst_id_t list_id, cur_id_t cursor, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::SUBSCRIBERS );
	req->set_GET_data( REC_ARGS_4( list_id, cursor, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::subscribe_to_list_request( lst_id_t list_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::SUBSCRIBERS );
	req->set_POST_data( REC_ARGS_1( list_id ) );
	return req;
}

TwitterRequest* RequestCreator::subscribe_to_list_request( slug_t slug, usr_name_t owner_screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::SUBSCRIBERS );
	req->set_POST_data( REC_ARGS_2( slug, owner_screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::show_user_is_suscriber_by_ids_request( usr_id_t user_id, lst_id_t list_id, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::SUBSCRIBERS );
	req->set_GET_data( REC_ARGS_4( user_id, list_id, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::show_user_is_suscriber_request( usr_name_t screen_name, lst_id_t slug, usr_name_t owner_screen_name, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::SUBSCRIBERS );
	req->set_GET_data( REC_ARGS_5( screen_name, slug, owner_screen_name, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::unsubscribe_from_list_request( lst_id_t list_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::SUBSCRIBERS );
	req->set_POST_data( REC_ARGS_1( list_id ) );
	return req;
}

TwitterRequest* RequestCreator::unsubscribe_from_list_request( slug_t slug, usr_name_t owner_screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::SUBSCRIBERS );
	req->set_POST_data( REC_ARGS_2( slug, owner_screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::subscribe_to_list_multi_by_ids_request( lst_id_t list_id, usr_id_t user_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::MEMBERS );
	req->set_POST_data( REC_ARGS_2( list_id, user_id ) );
	return req;
}

TwitterRequest* RequestCreator::subscribe_to_list_multi_request( slug_t slug, usr_name_t owner_screen_name, usr_name_t screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::MEMBERS );
	req->set_POST_data( REC_ARGS_3( slug, owner_screen_name, screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::show_user_is_member_by_ids_request( lst_id_t list_id, usr_id_t user_id, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::MEMBERS );
	req->set_GET_data( REC_ARGS_4( list_id, user_id, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::show_user_is_member_request( slug_t slug, usr_name_t owner_screen_name, usr_name_t screen_name, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::MEMBERS );
	req->set_GET_data( REC_ARGS_5( slug, owner_screen_name, screen_name, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::list_members_by_id_request( lst_id_t list_id, cur_id_t cursor, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::MEMBERS );
	req->set_GET_data( REC_ARGS_4( list_id, cursor, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::list_members_request( slug_t slug, usr_name_t owner_screen_name, cur_id_t cursor, bool include_entities, bool skip_status ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::MEMBERS );
	req->set_GET_data( REC_ARGS_5( slug, owner_screen_name, cursor, include_entities, skip_status ) );
	return req;
}

TwitterRequest* RequestCreator::join_list_request( usr_id_t user_id, lst_id_t list_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::MEMBERS );
	req->set_POST_data( REC_ARGS_2( user_id, list_id ) );
	return req;
}

TwitterRequest* RequestCreator::join_list_request( usr_name_t screen_name, slug_t slug, usr_name_t owner_screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::MEMBERS );
	req->set_POST_data( REC_ARGS_3( screen_name, slug, owner_screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::part_from_list_request( lst_id_t list_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::DESTROY );
	req->set_POST_data( REC_ARGS_1( list_id ) );
	return req;
}

TwitterRequest* RequestCreator::update_list_by_id_request( lst_id_t list_id, str_t name, str_t description, str_t mode ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::UPDATE );
	req->set_POST_data( REC_ARGS_4( list_id, name, description, mode ) );
	return req;
}

TwitterRequest* RequestCreator::update_list_request( slug_t slug, usr_name_t owner_screen_name, str_t name, str_t description, str_t mode ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::UPDATE );
	req->set_POST_data( REC_ARGS_5( slug, owner_screen_name, name, description, mode ) );
	return req;
}

TwitterRequest* RequestCreator::create_list_request( str_t name, str_t description, bool mode ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::CREATE );
	req->set_POST_data( REC_ARGS_3( name, description, mode ) );
	return req;
}

TwitterRequest* RequestCreator::show_list_request( lst_id_t list_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::SHOW );
	req->set_GET_data( REC_ARGS_1( list_id ) );
	return req;
}

TwitterRequest* RequestCreator::show_list_request( slug_t slug, usr_name_t owner_screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::SHOW );
	req->set_GET_data( REC_ARGS_2( slug, owner_screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::lists_subscription_by_id_request( usr_id_t user_id, int count, cur_id_t cursor ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::SUBSCRIPTIONS );
	req->set_GET_data( REC_ARGS_3( user_id, count, cursor ) );
	return req;
}

TwitterRequest* RequestCreator::lists_subscription_request( usr_name_t screen_name, int count, cur_id_t cursor ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::SUBSCRIPTIONS );
	req->set_GET_data( REC_ARGS_3( screen_name, count, cursor ) );
	return req;
}

TwitterRequest* RequestCreator::expulse_from_list_by_ids_request( lst_id_t list_id, usr_id_t user_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::MEMBERS );
	req->set_POST_data( REC_ARGS_2( list_id, user_id ) );
	return req;
}

TwitterRequest* RequestCreator::expulse_from_list_request( slug_t slug, usr_name_t owner_screen_name, usr_name_t screen_name ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::LISTS::MEMBERS );
	req->set_POST_data( REC_ARGS_3( slug, owner_screen_name, screen_name ) );
	return req;
}

TwitterRequest* RequestCreator::get_saved_searches_request(  ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::SAVED_SEARCHES::LIST );

	return req;
}

TwitterRequest* RequestCreator::show_saved_search_request( sch_id_t id ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::SAVED_SEARCHES::SHOW, id )
	 );

	return req;
}

TwitterRequest* RequestCreator::search_request( str_t query ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::SAVED_SEARCHES::CREATE );
	req->set_POST_data( REC_ARGS_1( query ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_saved_search_request( sch_id_t id ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::SAVED_SEARCHES::DESTROY, id )
	 );

	return req;
}

TwitterRequest* RequestCreator::trends_place_request( int id, str_t exclude ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::TRENDS::PLACE );
	req->set_GET_data( REC_ARGS_2( id, exclude ) );
	return req;
}

TwitterRequest* RequestCreator::available_trends_request(  ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::TRENDS::AVAILABLE );

	return req;
}

TwitterRequest* RequestCreator::closest_trend_request( float Lat, float Long ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::TRENDS::CLOSEST );
	req->set_GET_data( REC_ARGS_2( Lat, Long ) );
	return req;
}

TwitterRequest* RequestCreator::report_spam_request( usr_id_t user_id ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::REPORT_SPAM );
	req->set_POST_data( REC_ARGS_1( user_id ) );
	return req;
}

TwitterRequest* RequestCreator::rate_limit_status_request( str_t ressources ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::APPLICATION::RATE_LIMIT_STATUS );
	req->set_GET_data( REC_ARGS_1( ressources ) );
	return req;
}

TwitterRequest* RequestCreator::help_languages_request(  ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::HELP::LANGUAGES );

	return req;
}

TwitterRequest* RequestCreator::help_privacy_request(  ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::HELP::PRIVACY );

	return req;
}

TwitterRequest* RequestCreator::help_TOS_request(  ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::HELP::TOS );

	return req;
}

TwitterRequest* RequestCreator::application_rate_limit_status_request( str_t ressources ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::APPLICATION::RATE_LIMIT_STATUS );
	req->set_GET_data( REC_ARGS_1( ressources ) );
	return req;
}

TwitterRequest* RequestCreator::user_stream_request( str_t with, str_t replies, str_t track, str_t locations, bool delimited, bool stall_warnings ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STREAMS::USERSTREAM );
	req->set_GET_data( REC_ARGS_6( with, replies, track, locations, delimited, stall_warnings ) );
	return req;
}

/* END_PYGEN don't remove this comment (2012/10/27 14:35) */


/* MANUALLY (media uploads) */
TwitterRequest* RequestCreator::_update_status_with_media_request( str_t status, str_t in_reply_to_status_id, bool possibly_sensitive,  str_t place_id,  bool display_coordinates,  bool trim_user,  float lat,  float lon ) {

	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::UPDATE_WITH_MEDIA);

	req->add_form_data( "status", status );
	if ( in_reply_to_status_id != DEF_STR ) { req->add_form_data( "in_reply_to_status_id", in_reply_to_status_id ); }
	if ( possibly_sensitive ) { req->add_form_data( "possibly_sensitive", "true" ); }

	if ( place_id != DEF_STR ) { req->add_form_data( "place_id", place_id ); }

	if ( display_coordinates ) { req->add_form_data( "display_coordinates", "true" ); }
	if ( trim_user ) { req->add_form_data( "trim_user", "true" ); }
	if ( lon != DEF_NUM ) { req->add_form_data( "lon", Utils::otos(lon) ); }
	if ( lat != DEF_NUM) { req->add_form_data( "lat", Utils::otos(lat) ); }

	return req;

}


TwitterRequest* RequestCreator::update_status_with_media_request( str_t status, str_t media_path, str_t in_reply_to_status_id, bool possibly_sensitive,  str_t place_id,  bool display_coordinates,  bool trim_user,  float lat,  float lon ) {

	TwitterRequest* req = _update_status_with_media_request( status, in_reply_to_status_id, possibly_sensitive,  place_id,  display_coordinates,  trim_user,  lat,  lon );
	req->add_form_file( MEDIA_TAG, media_path );
	return req;

}

TwitterRequest* RequestCreator::update_status_with_media_request( str_t status, std::list<std::string> media_paths_list, str_t in_reply_to_status_id, bool possibly_sensitive,  str_t place_id,  bool display_coordinates,  bool trim_user,  float lat,  float lon ) {

	TwitterRequest* req = _update_status_with_media_request( status, in_reply_to_status_id, possibly_sensitive, place_id,  display_coordinates,  trim_user,  lat,  lon );
	
	std::list<std::string>::iterator iter;

	for ( iter = media_paths_list.begin(); iter != media_paths_list.end(); iter++ ) {
		req->add_form_file( MEDIA_TAG, (*iter) );
	}
	
	return req;

}
