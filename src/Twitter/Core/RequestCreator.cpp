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


TwitterRequest* RequestCreator::update_status_request( const std::string& status, int in_reply_to, bool display_coordinates,
						 					bool trim_user ) {

	PUT_VAR_IN_URL( TwitterConsts::Tweets::UPDATE, in_reply_to );
	TwitterRequest* req = __make_a_request( TwitterConsts::Tweets::UPDATE );
	req->set_POST_data( REC_ARGS_4( status, in_reply_to, display_coordinates, trim_user ) );

	return req;
}

TwitterRequest* RequestCreator::verify_credentials_request() {


	TwitterRequest* req = __make_a_request( TwitterConsts::Users::VERIFY_CREDENTIALS );

	return req;

}

TwitterRequest* RequestCreator::get_settings_request() {

	TwitterRequest* req = __make_a_request( TwitterConsts::Settings::GET_SETTINGS );

	return req;
}

TwitterRequest* RequestCreator::stream_user_request( std::string with, std::string track ) {

	TwitterRequest* req = __make_a_request( TwitterConsts::Streaming::STREAM_USER );
	req->set_POST_data( REC_ARGS_2( with, track ) );

	return req;

}

/* BEGIN_PYGEN don't remove this comment (2012/9/26 17:23) */
TwitterRequest* RequestCreator::mentions_timeline_request( int count, std::string since_id, int max_id, bool trim_user, bool contributor_details, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::MENTIONS_TIMELINE );
	req->set_GET_data( REC_ARGS_6( count, since_id, max_id, trim_user, contributor_details, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::user_timeline_request( int user_id, std::string screen_name, int count, int since_id, int max_id, bool trim_user, bool exclude_replies, bool contributor_details, bool include_rts ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::USER_TIMELINE );
	req->set_GET_data( REC_ARGS_9( user_id, screen_name, count, since_id, max_id, trim_user, exclude_replies, contributor_details, include_rts ) );
	return req;
}

TwitterRequest* RequestCreator::home_timeline_request( int count, int since_id, int max_id, bool trim_user, bool exclude_replies, bool contributor_details, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::HOME_TIMELINE );
	req->set_GET_data( REC_ARGS_7( count, since_id, max_id, trim_user, exclude_replies, contributor_details, include_entities ) );
	return req;
}

TwitterRequest* RequestCreator::retweets_request( std::string id, int count, bool trim_user ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::STATUSES::RETWEETS, id )
	 );
	req->set_GET_data( REC_ARGS_2( count, trim_user ) );
	return req;
}

TwitterRequest* RequestCreator::destroy_status_request( std::string id, bool trim_user ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::STATUSES::DESTROY, id )
	 );
	req->set_POST_data( REC_ARGS_1( trim_user ) );
	return req;
}

TwitterRequest* RequestCreator::update_status_request( std::string status, std::string in_reply_to_status_id, std::string place_id, bool display_coordinates, bool trim_user, float lat, float lon ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::UPDATE );
	req->set_POST_data( REC_ARGS_7( status, in_reply_to_status_id, place_id, display_coordinates, trim_user, lat, lon ) );
	return req;
}

TwitterRequest* RequestCreator::retweet_request( std::string id, bool trim_user ) {
	TwitterRequest* req = __make_a_request( 
		PUT_VAR_IN_URL( TwitterConsts::STATUSES::RETWEET, id )
	 );
	req->set_POST_data( REC_ARGS_1( trim_user ) );
	return req;
}

TwitterRequest* RequestCreator::oembed_status_request( std::string id, std::string url, int maxwidth, bool hide_media, bool hide_thread, bool omit_script, std::string align, std::string related, std::string lang ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::STATUSES::OEMBED );
	req->set_GET_data( REC_ARGS_9( id, url, maxwidth, hide_media, hide_thread, omit_script, align, related, lang ) );
	return req;
}

TwitterRequest* RequestCreator::search_tweets_request( std::string q, std::string locale, std::string result_type, int count, std::string until, std::string since_id, std::string max_id, bool include_entities, std::string callback ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::SEARCH::TWEETS );
	req->set_GET_data( REC_ARGS_9( q, locale, result_type, count, until, since_id, max_id, include_entities, callback ) );
	return req;
}

TwitterRequest* RequestCreator::sent_direct_messages_request( int count, int page, std::string since_id, std::string max_id, bool include_entities ) {
	TwitterRequest* req = __make_a_request( TwitterConsts::DIRECT_MESSAGES::SENT );
	req->set_GET_data( REC_ARGS_5( count, page, since_id, max_id, include_entities ) );
	return req;
}

/* END_PYGEN don't remove this comment (2012/9/26 17:23) */

