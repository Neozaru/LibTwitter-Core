#ifndef H_TWITTERCONSTANTS_H
	#define H_TWITTERCONSTANTS_H

	#include <string>

	using namespace std;
	



const std::string DEFAULT_PROXY = "system_defined";

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





namespace TwitterConsts {



	const string API_LINK = "http://api.twitter.com/1.1/";


	const string ACCOUNT = "account/";


/* BEGIN_PYGEN don't remove this comment (2012/9/25 23:11) */

	namespace STATUSES {

		const std::string STATUSES = "statuses/";

		const std::string MENTIONS_TIMELINE = STATUSES+"mentions_timeline";
		const std::string USER_TIMELINE = STATUSES+"user_timeline";
		const std::string HOME_TIMELINE = STATUSES+"home_timeline";
	};

/* END_PYGEN don't remove this comment (2012/9/25 23:11) */

	namespace Streaming {

		const string STREAM_USER = "https://userstream.twitter.com/1.1/user.json";

	};


	namespace Tweets {

		const string UPDATE = API_LINK + "statuses/" + "update.json";

	}

	namespace Users {

		const string VERIFY_CREDENTIALS = API_LINK + ACCOUNT + "verify_credentials.json";

	}

	namespace Settings {

		const string GET_SETTINGS = API_LINK + ACCOUNT + "settings.json";

	}
	
};

#endif