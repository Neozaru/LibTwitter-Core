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

TwitterRequest* RequestCreator::get_mentions_timeline_request( int count,  float since_id, int max_id, int trim_user, 
										bool contributor_details,  bool include_entities ) {

	TwitterRequest* req = __make_a_request( TwitterConsts::Statuses::Timelines::MENTIONS_TIMELINE );
	req->set_GET_data( REC_ARGS_6(count,since_id,max_id,trim_user,contributor_details,include_entities) );

	return req;
}

TwitterRequest* RequestCreator::update_status_request( const std::string& status, int in_reply_to, bool display_coordinates,
						 					bool trim_user ) {

	PUT_VAR_IN_URL( TwitterConsts::Statuses::Tweets::UPDATE, in_reply_to );
	TwitterRequest* req = __make_a_request( TwitterConsts::Statuses::Tweets::UPDATE );
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


