#ifndef H_TWITTERCONSTANTS_H
	#define H_TWITTERCONSTANTS_H

	#include <string>

	using namespace std;
	
	typedef const std::string& str_t;

	typedef std::string twt_id_t;
	typedef std::string cur_id_t;
	typedef std::string usr_id_t;
	
	typedef std::string slug_t;
	typedef std::string lang_t;
	typedef std::string usr_name_t;

	//typedef unsigned int lst_id_t;
	//typedef unsigned int sch_id_t;
	//typedef unsigned int msg_id_t;

	typedef std::string lst_id_t;
	typedef std::string sch_id_t;
	typedef std::string msg_id_t;

const std::string DEFAULT_PROXY = "system_defined";

enum e_debug_levels {
	NONE = 0,
	DEBUG,
	WARNINGS,
	ERRORS,
	NB_DEBUG_LEVELS
};



enum e_HTTP_request_type {
    INVALID = 0,
    GET,
    POST,
    DELETE
};


namespace e_HTTP_response_code {

	enum e_HTTP_response_code {
		UNDEFINED = 999,
		WAITING_RESPONSE = 1000,
		
		OK = 200,
		RATE_LIMIT = 88,
		MEDIA_LIMIT = 192,
		NOT_FOUND = 404,
		NOT_ACCEPTABLE = 406,
		FLOOD = 429,

		NB_HTTP_CODES = 7
	};

};

/*
static const char* e_HTTP_response_code_Text[] {
	"No request !",
	"Waiting response ...",
	"OK",
	"Target not found",
	"Flood",
	"Not acceptable"
};
*/

const std::string MEDIA_TAG = "media[]";



namespace TwitterConsts {

	const string API_VERSION = "1.1";

	const string PROTOCOL = "https://";

	const string API_LINK = PROTOCOL + "api.twitter.com/"+API_VERSION+"/";
	const string STREAM_API_LINK = "http://stream.twitter.com/"+API_VERSION+"/";

	const string FORMAT  = ".json";


	const string REPORT_SPAM = API_LINK + "report_spam";


/* BEGIN_PYGEN don't remove this comment (2012/10/27 14:35) */

	namespace STATUSES {

		const std::string STATUSES = "statuses/";

		const std::string MENTIONS_TIMELINE = API_LINK + STATUSES + "mentions_timeline" + FORMAT ;
		const std::string USER_TIMELINE = API_LINK + STATUSES + "user_timeline" + FORMAT ;
		const std::string HOME_TIMELINE = API_LINK + STATUSES + "home_timeline" + FORMAT ;
		const std::string RETWEETS = API_LINK + STATUSES + "retweets/:id" + FORMAT ;
		const std::string SHOW = API_LINK + STATUSES + "show/:id" + FORMAT ;
		const std::string DESTROY = API_LINK + STATUSES + "destroy/:id" + FORMAT ;
		const std::string UPDATE = API_LINK + STATUSES + "update" + FORMAT ;
		const std::string RETWEET = API_LINK + STATUSES + "retweet/:id" + FORMAT ;
		const std::string OEMBED = API_LINK + STATUSES + "oembed" + FORMAT ;
	};

	namespace SEARCH {

		const std::string SEARCH = "search/";

		const std::string TWEETS = API_LINK + SEARCH + "tweets" + FORMAT ;
	};

	namespace DIRECT_MESSAGES {

		const std::string DIRECT_MESSAGES = "direct_messages/";

		const std::string SENT = API_LINK + DIRECT_MESSAGES + "sent" + FORMAT ;
		const std::string SHOW = API_LINK + DIRECT_MESSAGES + "show" + FORMAT ;
		const std::string DESTROY = API_LINK + DIRECT_MESSAGES + "destroy" + FORMAT ;
		const std::string NEW = API_LINK + DIRECT_MESSAGES + "new" + FORMAT ;
	};

	namespace FRIENDS {

		const std::string FRIENDS = "friends/";

		const std::string IDS = API_LINK + FRIENDS + "ids" + FORMAT ;
	};

	namespace FOLLOWERS {

		const std::string FOLLOWERS = "followers/";

		const std::string IDS = API_LINK + FOLLOWERS + "ids" + FORMAT ;
	};

	namespace FRIENDSHIPS {

		const std::string FRIENDSHIPS = "friendships/";

		const std::string LOOKUP = API_LINK + FRIENDSHIPS + "lookup" + FORMAT ;
		const std::string INCOMING = API_LINK + FRIENDSHIPS + "incoming" + FORMAT ;
		const std::string OUTGOING = API_LINK + FRIENDSHIPS + "outgoing" + FORMAT ;
		const std::string CREATE = API_LINK + FRIENDSHIPS + "create" + FORMAT ;
		const std::string DESTROY = API_LINK + FRIENDSHIPS + "destroy" + FORMAT ;
		const std::string UPDATE = API_LINK + FRIENDSHIPS + "update" + FORMAT ;
		const std::string SHOW = API_LINK + FRIENDSHIPS + "show" + FORMAT ;
	};

	namespace ACCOUNT {

		const std::string ACCOUNT = "account/";

		const std::string VERIFY_CREDENTIALS = API_LINK + ACCOUNT + "verify_credentials" + FORMAT ;
		const std::string SETTINGS = API_LINK + ACCOUNT + "settings" + FORMAT ;
		const std::string UPDATE_DELIVERY_DEVICE = API_LINK + ACCOUNT + "update_delivery_device" + FORMAT ;
		const std::string UPDATE_PROFILE = API_LINK + ACCOUNT + "update_profile" + FORMAT ;
		const std::string UPDATE_PROFILE_BACKGROUND_IMAGE = API_LINK + ACCOUNT + "update_profile_background_image" + FORMAT ;
		const std::string UPDATE_PROFILE_COLORS = API_LINK + ACCOUNT + "update_profile_colors" + FORMAT ;
	};

	namespace BLOCKS {

		const std::string BLOCKS = "blocks/";

		const std::string LIST = API_LINK + BLOCKS + "list" + FORMAT ;
		const std::string IDS = API_LINK + BLOCKS + "ids" + FORMAT ;
		const std::string CREATE = API_LINK + BLOCKS + "create" + FORMAT ;
		const std::string DESTROY = API_LINK + BLOCKS + "destroy" + FORMAT ;
	};

	namespace USERS {

		const std::string USERS = "users/";

		const std::string LOOKUP = API_LINK + USERS + "lookup" + FORMAT ;
		const std::string SHOW = API_LINK + USERS + "show" + FORMAT ;
		const std::string SEARCH = API_LINK + USERS + "search" + FORMAT ;
		const std::string CONTRIBUTEES = API_LINK + USERS + "contributees" + FORMAT ;
		const std::string CONTRIBUTORS = API_LINK + USERS + "contributors" + FORMAT ;
		const std::string SUGGESTIONS = API_LINK + USERS + "suggestions/:slug" + FORMAT ;
	};

	namespace FAVORITES {

		const std::string FAVORITES = "favorites/";

		const std::string LIST = API_LINK + FAVORITES + "list" + FORMAT ;
		const std::string DESTROY = API_LINK + FAVORITES + "destroy" + FORMAT ;
		const std::string CREATE = API_LINK + FAVORITES + "create" + FORMAT ;
	};

	namespace LISTS {

		const std::string LISTS = "lists/";

		const std::string LIST = API_LINK + LISTS + "list" + FORMAT ;
		const std::string STATUSES = API_LINK + LISTS + "statuses" + FORMAT ;
		const std::string MEMBERS = API_LINK + LISTS + "members/destroy" + FORMAT ;
		const std::string MEMBERSHIPS = API_LINK + LISTS + "memberships" + FORMAT ;
		const std::string SUBSCRIBERS = API_LINK + LISTS + "subscribers" + FORMAT ;
		const std::string DESTROY = API_LINK + LISTS + "destroy" + FORMAT ;
		const std::string UPDATE = API_LINK + LISTS + "update" + FORMAT ;
		const std::string CREATE = API_LINK + LISTS + "create" + FORMAT ;
		const std::string SHOW = API_LINK + LISTS + "show" + FORMAT ;
		const std::string SUBSCRIPTIONS = API_LINK + LISTS + "subscriptions" + FORMAT ;
	};

	namespace SAVED_SEARCHES {

		const std::string SAVED_SEARCHES = "saved_searches/";

		const std::string LIST = API_LINK + SAVED_SEARCHES + "list" + FORMAT ;
		const std::string SHOW = API_LINK + SAVED_SEARCHES + "show/:id" + FORMAT ;
		const std::string CREATE = API_LINK + SAVED_SEARCHES + "create" + FORMAT ;
		const std::string DESTROY = API_LINK + SAVED_SEARCHES + "destroy/:id" + FORMAT ;
	};

	namespace TRENDS {

		const std::string TRENDS = "trends/";

		const std::string PLACE = API_LINK + TRENDS + "place" + FORMAT ;
		const std::string AVAILABLE = API_LINK + TRENDS + "available" + FORMAT ;
		const std::string CLOSEST = API_LINK + TRENDS + "closest" + FORMAT ;
	};

	namespace APPLICATION {

		const std::string APPLICATION = "application/";

		const std::string RATE_LIMIT_STATUS = API_LINK + APPLICATION + "rate_limit_status" + FORMAT ;
	};

	namespace HELP {

		const std::string HELP = "help/";

		const std::string LANGUAGES = API_LINK + HELP + "languages" + FORMAT ;
		const std::string PRIVACY = API_LINK + HELP + "privacy" + FORMAT ;
		const std::string TOS = API_LINK + HELP + "tos" + FORMAT ;
	};

	namespace STREAMS {

		const std::string STREAMS = "streams/";

		const std::string USERSTREAM = PROTOCOL + "" + "userstream.twitter.com/1.1/user" + FORMAT ;
	};

/* END_PYGEN don't remove this comment (2012/10/27 14:35) */

	namespace STATUSES {

		const std::string UPDATE_WITH_MEDIA = API_LINK + "statuses/" + "update_with_media" + FORMAT ;	
	
	};

	namespace Streaming {

		const string STREAM_USER = "https://userstream.twitter.com/1.1/user.json";

	};


	namespace Tweets {

		const string UPDATE = API_LINK + "statuses/" + "update.json";

	};


};

#endif