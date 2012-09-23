/**
* \file OAuth.h File provided by TwitCurl C++ library --> https://code.google.com/p/twitcurl/
* \brief OAuth.h File provided by TwitCurl C++ library --> https://code.google.com/p/twitcurl/
* This file is and will be modified in order to improve performance and readability with the rest of LibTwitter
*/

#ifndef H_OAUTHLIB_H
#define H_OAUTHLIB_H

#include "time.h"
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

#include "TwitterConstants.h"


namespace OAuthConsts {

    /* Constants */
    const int BUFFSIZE = 1024;
    const int BUFFSIZE_LARGE = 1024;
    const std::string consumer_key_KEY = "oauth_consumer_key";
    const std::string CALLBACK_KEY = "oauth_callback";
    const std::string VERSION_KEY = "oauth_version";
    const std::string SIGNATUREMETHOD_KEY = "oauth_signature_method";
    const std::string SIGNATURE_KEY = "oauth_signature";
    const std::string TIMESTAMP_KEY = "oauth_timestamp";
    const std::string NONCE_KEY = "oauth_nonce";
    const std::string TOKEN_KEY = "oauth_token";
    const std::string TOKENSECRET_KEY = "oauth_token_secret";
    const std::string VERIFIER_KEY = "oauth_verifier";
    const std::string SCREENNAME_KEY = "screen_name";
    const std::string AUTHENTICITY_TOKEN_KEY = "authenticity_token";
    const std::string SESSIONUSERNAME_KEY = "session[username_or_email]";
    const std::string SESSIONPASSWORD_KEY = "session[password]";
    const std::string AUTHENTICITY_TOKEN_TWITTER_RESP_KEY = "authenticity_token\" type=\"hidden\" value=\"";
    const std::string TOKEN_TWITTER_RESP_KEY = "oauth_token\" type=\"hidden\" value=\"";
    const std::string PIN_TWITTER_RESP_KEY = "code-desc\"><code>";
    const std::string TOKEN_END_TAG_TWITTER_RESP = "\" />";
    const std::string PIN_END_TAG_TWITTER_RESP = "</code>";

    const std::string AUTHHEADER_STRING = "Authorization: OAuth ";

    /* Twitter OAuth API URLs */
    const std::string TWITTER_REQUEST_TOKEN_URL = "twitter.com/oauth/request_token";
    const std::string TWITTER_AUTHORIZE_URL = "twitter.com/oauth/authorize?oauth_token=";
    const std::string TWITTER_ACCESS_TOKEN_URL = "twitter.com/oauth/access_token";
};

typedef std::list<std::string> oAuthKeyValueList;
//typedef std::map<std::string, std::string> oAuthKeyValuePairs;

class OAuth {
public:
    OAuth();
    ~OAuth();

    /* OAuth public methods used by twitCurl */
    const std::string& get_consumer_key();
    void set_consumer_key( const std::string& consumer_key /* in */ );

    const std::string& get_consumer_secret();
    void set_consumer_secret( const std::string& consumerSecret /* in */ );

    const std::string& get_token_key();
    void set_token_key( const std::string& oAuthTokenKey /* in */ );

    const std::string& get_token_secret();
    void set_token_secret( const std::string& oAuthTokenSecret /* in */ );

    const std::string& get_username();
    void set_username( const std::string& oAuthScreenName /* in */ );

    const std::string& get_PIN_code();
    void set_PIN_code( const std::string& oAuthPin /* in */ );

    std::string get_oauth_header( const e_HTTP_request_type method, /* in */
                         const std::string& rawUrl, /* in */
                         const std::string& rawData, /* in */
                         const bool includeOAuthVerifierPin = false /* in */ );

    bool extract_oauth_token_key_secret( const std::string& requestTokenResponse /* in */ );

    OAuth clone();

private:

    /* OAuth data */
    std::string _consumer_key;
    std::string _consumer_secret;
    std::string _token_key;
    std::string _token_secret;
    std::string _pin;
    std::string _nonce;
    std::string _timestamp;
    std::string _username;

    /* OAuth twitter related utility methods */
    std::map<std::string, std::string> buildOAuthRawDataKeyValPairs( const std::string& rawData, /* in */
                                       bool urlencodeData /* in */  );

    bool buildOAuthTokenKeyValuePairs( const bool includeOAuthVerifierPin, /* in */
                                       const std::string& oauthSignature, /* in */
                                       std::map<std::string, std::string>& keyValueMap /* out */,
                                       const bool generateTimestamp /* in */ );

    bool getStringFromOAuthKeyValuePairs( const std::map<std::string, std::string>& rawParamMap, /* in */
                                          std::string& rawParams, /* out */
                                          const std::string& paramsSeperator /* in */ );

    bool getSignature( const e_HTTP_request_type method, /* in */
                       const std::string& rawUrl, /* in */
                       const std::map<std::string, std::string>& rawKeyValuePairs, /* in */
                       std::string& oAuthSignature /* out */ );

    void generateNonceTimeStamp();
};

#endif // H_OAUTHLIB_H
