/**
* File provided by TwitCurl C++ library --> https://code.google.com/p/twitcurl/
* This file is and will be modified in order to improve performance and readability with the rest of LibTwitter
*/

#include "OAuth.h"

#include "Utils/HMAC_SHA1.h"
#include "Utils/base64.h"
#include "Utils/urlencode.h"
#include "Utils.h"

/*++
* \fn OAuth::oAuth
*
* \brief constructor
*
* \param none
*
* \return none
*
*--*/
OAuth::OAuth() {}

/*++
* \fn OAuth::~oAuth
*
* \brief destructor
*
* \param none
*
* \return none
*
*--*/
OAuth::~OAuth() {}

/*++
* \fn OAuth::clone
*
* \brief creates a clone of oAuth object
*
* \param none
*
* \return cloned oAuth object
*
*--*/
OAuth OAuth::clone() {
    OAuth cloneObj;
    cloneObj._consumer_key = _consumer_key;
    cloneObj._consumer_secret = _consumer_secret;
    cloneObj._token_key = _token_key;
    cloneObj._token_secret = _token_secret;
    cloneObj._pin = _pin;
    cloneObj._nonce = _nonce;
    cloneObj._timestamp = _timestamp;
    cloneObj._username =  _username;
    return cloneObj;
}


/*++
* \fn OAuth::get_consumer_key
*
* \brief this method gives consumer key that is being used currently
*
* \param none
*
* \return consumer key
*
*--*/
const std::string& OAuth::get_consumer_key() {
    return _consumer_key;
}

/*++
* \fn OAuth::set_consumer_key
*
* \brief this method saves consumer key that should be used
*
* \param consumer key
*
* \return none
*
*--*/
void OAuth::set_consumer_key( const std::string& consumer_key )
{
    _consumer_key.assign( consumer_key );
}

/*++
* \fn OAuth::get_consumer_secret
*
* \brief this method gives consumer secret that is being used currently
*
* \param none
*
* \return Consumer secret
*
*--*/
const std::string& OAuth::get_consumer_secret() {
    return _consumer_secret;
}

/*++
* \fn OAuth::set_consumer_secret
*
* \brief this method saves consumer secret that should be used
*
* \param consumer secret
*
* \return none
*
*--*/
void OAuth::set_consumer_secret( const std::string& consumerSecret )
{
    _consumer_secret = consumerSecret;
}

/*++
* \fn OAuth::get_token_key
*
* \brief this method gives OAuth token (also called access token) that is being used currently
*
* \param none
*
* \return OAuth token
*
*--*/
const std::string& OAuth::get_token_key() {
    return _token_key;
}

/*++
* \fn OAuth::set_token_key
*
* \brief this method saves OAuth token that should be used
*
* \param OAuth token
*
* \return none
*
*--*/
void OAuth::set_token_key( const std::string& oAuthTokenKey )
{
    _token_key = oAuthTokenKey;
}

/*++
* \fn OAuth::get_token_secret
*
* \brief this method gives OAuth    token secret that is being used currently
*
* \param none
*
* \return OAuth token secret
*
*--*/
const std::string& OAuth::get_token_secret() {
    return _token_secret;
}

/*++
* \fn OAuth::set_token_secret
*
* \brief this method saves OAuth token that should be used
*
* \param OAuth token secret
*
* \return none
*
*--*/
void OAuth::set_token_secret( const std::string& oAuthTokenSecret ) {
    _token_secret = oAuthTokenSecret;
}

/*++
* \fn OAuth::get_username
*
* \brief this method gives authorized user's screenname
*
* \param none
*
* \return screen name
*
*--*/
const std::string& OAuth::get_username() {
    return _username;
}

/*++
* \fn OAuth::set_username
*
* \brief this method sets authorized user's screenname
*
* \param screen name
*
* \return none
*
*--*/
void OAuth::set_username( const std::string& oAuthScreenName ) {
    _username = oAuthScreenName;
}

/*++
* \fn OAuth::get_PIN_code
*
* \brief this method gives OAuth verifier PIN
*
* \param none
*
* \return OAuth verifier PIN
*
*--*/
const std::string& OAuth::get_PIN_code() {
    return _pin;
}

/*++
* \fn OAuth::set_PIN_code
*
* \brief this method sets OAuth verifier PIN
*
* \param OAuth verifier PIN
*
* \return none
*
*--*/
void OAuth::set_PIN_code( const std::string& oAuthPin ) {
    _pin = oAuthPin;
}

/*++
* \fn OAuth::generateNonceTimeStamp
*
* \brief this method generates nonce and timestamp for OAuth header
*
* \param none
*
* \return none
*
* @remarks: internal method
*
*--*/
void OAuth::generateNonceTimeStamp() {

    char szTime[OAuthConsts::BUFFSIZE];
    char szRand[OAuthConsts::BUFFSIZE];
    memset( szTime, 0, OAuthConsts::BUFFSIZE );
    memset( szRand, 0, OAuthConsts::BUFFSIZE );
    srand( time( NULL ) );
    sprintf( szRand, "%x", rand()%1000 );
    sprintf( szTime, "%ld", time( NULL ) );

    _nonce.assign( szTime );
    _nonce.append( szRand );
    _timestamp.assign( szTime );
}

/*++
* \fn OAuth::buildOAuthRawDataKeyValPairs
*
* \brief this method prepares key-value pairs from the data part of the URL
*               or from the URL post fields data, as required by OAuth header
*               and signature generation.
*
* \param rawData - Raw data either from the URL itself or from post fields.
*                   Should already be url encoded.
*         urlencodeData - If true, string will be urlencoded before converting
*                         to key value pairs.
*
* \return rawDataKeyValuePairs - Map in which key-value pairs are populated
*
* @remarks: internal method
*
*--*/
std::map<std::string, std::string> OAuth::buildOAuthRawDataKeyValPairs( const std::string& rawData,
                                          bool urlencodeData ) {
    
    std::map<std::string, std::string> rawDataKeyValuePairs;
    /* Raw data if it's present. Data should already be urlencoded once */
    if( rawData.length() ) {
        size_t nSep = std::string::npos;
        size_t nPos = std::string::npos;
        std::string dataKeyVal;
        std::string dataKey;
        std::string dataVal;

        /* This raw data part can contain many key value pairs: key1=value1&key2=value2&key3=value3 */
        std::string dataPart = rawData;
        while( std::string::npos != ( nSep = dataPart.find_first_of("&") ) ) {
            /* Extract first key=value pair */
            dataKeyVal = dataPart.substr( 0, nSep );

            /* Split them */
            nPos = dataKeyVal.find_first_of( "=" );
            if( std::string::npos != nPos ) {
                dataKey = dataKeyVal.substr( 0, nPos );
                dataVal = dataKeyVal.substr( nPos + 1 );

                /* Put this key=value pair in map */
                rawDataKeyValuePairs[dataKey] = urlencodeData ? urlencode( dataVal ) : dataVal;
            }
            dataPart = dataPart.substr( nSep + 1 );
        }

        /* For the last key=value */
        dataKeyVal = dataPart.substr( 0, nSep );

        /* Split them */
        nPos = dataKeyVal.find_first_of( "=" );
        if( std::string::npos != nPos )
        {
            dataKey = dataKeyVal.substr( 0, nPos );
            dataVal = dataKeyVal.substr( nPos + 1 );

            /* Put this key=value pair in map */
            rawDataKeyValuePairs[dataKey] = urlencodeData ? urlencode( dataVal ) : dataVal;
        
        }
    }
    return rawDataKeyValuePairs;
}

/*++
* \fn OAuth::buildOAuthTokenKeyValuePairs
*
* \brief this method prepares key-value pairs required for OAuth header
*               and signature generation.
*
* \param includeOAuthVerifierPin - flag to indicate whether oauth_verifer key-value
*                                   pair needs to be included. oauth_verifer is only
*                                   used during exchanging request token with access token.
*         oauthSignature - base64 and url encoded OAuth signature.
*         generateTimestamp - If true, then generate new timestamp for nonce.
*
* \return keyValueMap - map in which key-value pairs are populated
*
* @remarks: internal method
*
*--*/
bool OAuth::buildOAuthTokenKeyValuePairs( const bool includeOAuthVerifierPin,
                                          const std::string& oauthSignature,
                                          std::map<std::string, std::string>& keyValueMap,
                                          const bool generateTimestamp )
{
    /* Generate nonce and timestamp if required */
    if( generateTimestamp ) {
        generateNonceTimeStamp();
    }

    /* Consumer key and its value */
    keyValueMap[OAuthConsts::consumer_key_KEY] = _consumer_key;

    /* Nonce key and its value */
    keyValueMap[OAuthConsts::NONCE_KEY] = _nonce;

    /* Signature if supplied */
    if( oauthSignature.length() > 0 ) {
        keyValueMap[OAuthConsts::SIGNATURE_KEY] = oauthSignature;
    }

    /* Signature method, only HMAC-SHA1 as of now */
    keyValueMap[OAuthConsts::SIGNATUREMETHOD_KEY] = std::string( "HMAC-SHA1" );

    /* Timestamp */
    keyValueMap[OAuthConsts::TIMESTAMP_KEY] = _timestamp;

    /* Token */
    if( _token_key.length() > 0 ) {
        keyValueMap[OAuthConsts::TOKEN_KEY] = _token_key;
    }

    /* Verifier */
    if( includeOAuthVerifierPin && _pin.length() ) {
        keyValueMap[OAuthConsts::VERIFIER_KEY] = _pin;
    }

    /* Version */
    keyValueMap[OAuthConsts::VERSION_KEY] = std::string( "1.0" );

    return ( keyValueMap.size() > 0 );
}

/*++
* \fn OAuth::getSignature
*
* \brief this method calculates HMAC-SHA1 signature of OAuth header
*
* \param eType - HTTP request type
*         rawUrl - raw url of the HTTP request
*         rawKeyValuePairs - key-value pairs containing OAuth headers and HTTP data
*
* \return oAuthSignature - base64 and url encoded signature
*
* @remarks: internal method
*
*--*/
bool OAuth::getSignature( const e_HTTP_request_type method,
                          const std::string& rawUrl,
                          const std::map<std::string, std::string>& rawKeyValuePairs,
                          std::string& oAuthSignature ) {

    std::string rawParams;
    std::string paramsSeperator;
    std::string sigBase;

    /* Initially empty signature */
    oAuthSignature.assign( "" );

    /* Build a string using key-value pairs */
    paramsSeperator = "&";
    getStringFromOAuthKeyValuePairs( rawKeyValuePairs, rawParams, paramsSeperator );

    /* Start constructing base signature string. Refer http://dev.twitter.com/auth#intro */
    switch( method ) {

        case GET:
            sigBase.assign( "GET&" );
            break;

        case POST:
            sigBase.assign( "POST&" );
            break;

        case DELETE:
            sigBase.assign( "DELETE&" );
            break;

        default:
            return false;
            break;

    }

    sigBase.append( urlencode( rawUrl ) );
    sigBase.append( "&" );
    sigBase.append( urlencode( rawParams ) );

    /* Now, hash the signature base string using HMAC_SHA1 class */
    CHMAC_SHA1 objHMACSHA1;
    std::string secretSigningKey;
    unsigned char strDigest[OAuthConsts::BUFFSIZE_LARGE];

    memset( strDigest, 0, OAuthConsts::BUFFSIZE_LARGE );

    /* Signing key is composed of consumer_secret&token_secret */
    secretSigningKey.assign( _consumer_secret );
    secretSigningKey.append( "&" );

    if( _token_secret.length() ) {
        secretSigningKey.append( _token_secret );
    }
  
    objHMACSHA1.HMAC_SHA1( (unsigned char*)sigBase.c_str(),
                           sigBase.length(),
                           (unsigned char*)secretSigningKey.c_str(),
                           secretSigningKey.length(),
                           strDigest ); 

    /* Do a base64 encode of signature */
    std::string base64Str = base64_encode( strDigest, 20 /* SHA 1 digest is 160 bits */ );

    /* Do an url encode */
    oAuthSignature = urlencode( base64Str );

    return ( oAuthSignature.length() ) ? true : false;
}

/*++
* \fn OAuth::get_oauth_header
*
* \brief this method builds OAuth header that should be used in HTTP requests to twitter
*
* \param eType - HTTP request type
*         rawUrl - raw url of the HTTP request
*         rawData - HTTP data (post fields)
*         includeOAuthVerifierPin - flag to indicate whether or not oauth_verifier needs to included
*                                   in OAuth header
*
* \return oAuthHttpHeader - OAuth header
*
*--*/
std::string OAuth::get_oauth_header( const e_HTTP_request_type method,
                            const std::string& rawUrl,
                            const std::string& rawData,
                            const bool includeOAuthVerifierPin ) {
    
    std::string oAuthHttpHeader;

    std::map<std::string, std::string> rawKeyValuePairs;
    std::string rawParams;
    std::string oauthSignature;
    std::string paramsSeperator;
    std::string pureUrl( rawUrl );

    Utils::debug("----------------------");
    Utils::debug("oAuthHeader INPUT :");
    Utils::debug("URL : " + rawUrl);
    Utils::debug("Data : " + rawData);
    Utils::debug("Header : " + oAuthHttpHeader);


    /* Clear header string initially */
    oAuthHttpHeader.assign( "" );
    rawKeyValuePairs.clear();

    /* If URL itself contains ?key=value, then extract and put them in map */
    size_t nPos = rawUrl.find_first_of( "?" );
    if( std::string::npos != nPos ) {
        /* Get only URL */
        pureUrl = rawUrl.substr( 0, nPos );

        /* Get only key=value data part */
        std::string dataPart = rawUrl.substr( nPos + 1 );

        /* Split the data in URL as key=value pairs */
        rawKeyValuePairs = buildOAuthRawDataKeyValPairs( dataPart, true );
    }

    /* Split the raw data if it's present, as key=value pairs. Data should already be urlencoded once */
    rawKeyValuePairs = buildOAuthRawDataKeyValPairs( rawData, false );

    /* Build key-value pairs needed for OAuth request token, without signature */
    buildOAuthTokenKeyValuePairs( includeOAuthVerifierPin, std::string( "" ), rawKeyValuePairs, true );

    /* Get url encoded base64 signature using request type, url and parameters */
    getSignature( method, pureUrl, rawKeyValuePairs, oauthSignature );

    /* Clear map so that the parameters themselves are not sent along with the OAuth values */
    rawKeyValuePairs.clear();

    /* Now, again build key-value pairs with signature this time */
    buildOAuthTokenKeyValuePairs( includeOAuthVerifierPin, oauthSignature, rawKeyValuePairs, false );

    /* Get OAuth header in string format */
    paramsSeperator = ",";
    getStringFromOAuthKeyValuePairs( rawKeyValuePairs, rawParams, paramsSeperator );

    /* Build authorization header */
    oAuthHttpHeader.assign( OAuthConsts::AUTHHEADER_STRING );
    oAuthHttpHeader.append( rawParams );

    Utils::debug("++++++++++++++++++++++");
    Utils::debug("oAuthHeader OUPUT : ");
    Utils::debug("URL : " + rawUrl);
    Utils::debug("Data : " + rawData);
    Utils::debug("Header : " + oAuthHttpHeader);

    return oAuthHttpHeader;
}

/*++
* \fn OAuth::getStringFromOAuthKeyValuePairs
*
* \brief this method builds a sorted string from key-value pairs
*
* \param rawParamMap - key-value pairs map
*         paramsSeperator - sepearator, either & or ,
*
* \return rawParams - sorted string of OAuth parameters
*
* @remarks: internal method
*
*--*/
bool OAuth::getStringFromOAuthKeyValuePairs( const std::map<std::string, std::string>& rawParamMap,
                                             std::string& rawParams,
                                             const std::string& paramsSeperator ) {
    rawParams.assign( "" );
    if( rawParamMap.size() ) {
        oAuthKeyValueList keyValueList;
        std::string dummyStr;

        /* Push key-value pairs to a list of strings */
        keyValueList.clear();
        std::map<std::string, std::string>::const_iterator itMap = rawParamMap.begin();
        for( ; itMap != rawParamMap.end(); itMap++ ) {

            dummyStr.assign( itMap->first );
            dummyStr.append( "=" );
            
            if( paramsSeperator == "," ) {
                dummyStr.append( "\"" );
            }

            dummyStr.append( itMap->second );
            
            if( paramsSeperator == "," ) {
                dummyStr.append( "\"" );
            }
            
            keyValueList.push_back( dummyStr );
        }

        /* Sort key-value pairs based on key name */
        keyValueList.sort();

        /* Now, form a string */
        dummyStr.assign( "" );
        oAuthKeyValueList::iterator itKeyValue = keyValueList.begin();
        for( ; itKeyValue != keyValueList.end(); itKeyValue++ ) {

            if( dummyStr.length() ) {
                dummyStr.append( paramsSeperator );
            }

            dummyStr.append( itKeyValue->c_str() );
        }

        rawParams.assign( dummyStr );
    }

    return ( rawParams.length() ) ? true : false;
}

/*++
* \fn OAuth::extract_oauth_token_key_secret
*
* \brief this method extracts oauth token key and secret from
*               twitter's HTTP response
*
* \param requestTokenResponse - response from twitter
*
* \return none
*
*--*/
bool OAuth::extract_oauth_token_key_secret( const std::string& requestTokenResponse ) {

    if( requestTokenResponse.length() ) {

        size_t nPos = std::string::npos;
        std::string strDummy;

        /* Get oauth_token key */
        nPos = requestTokenResponse.find( OAuthConsts::TOKEN_KEY );
        if( std::string::npos != nPos ) {

            nPos = nPos + OAuthConsts::TOKEN_KEY.length() + strlen( "=" );
            strDummy = requestTokenResponse.substr( nPos );
            nPos = strDummy.find( "&" );
            if( std::string::npos != nPos ) {
                _token_key = strDummy.substr( 0, nPos );
            }
        }

        /* Get oauth_token_secret */
        nPos = requestTokenResponse.find( OAuthConsts::TOKENSECRET_KEY );
        if( std::string::npos != nPos ) {

            nPos = nPos + OAuthConsts::TOKENSECRET_KEY.length() + strlen( "=" );
            strDummy = requestTokenResponse.substr( nPos );
            nPos = strDummy.find( "&" );
            if( std::string::npos != nPos ) {
                _token_secret = strDummy.substr( 0, nPos );
            }
        }

        /* Get screen_name */
        nPos = requestTokenResponse.find( OAuthConsts::SCREENNAME_KEY );
        if( std::string::npos != nPos ) {
            nPos = nPos + OAuthConsts::SCREENNAME_KEY.length() + strlen( "=" );
            strDummy = requestTokenResponse.substr( nPos );
            _username = strDummy;
        }
    }
    return true;
}
