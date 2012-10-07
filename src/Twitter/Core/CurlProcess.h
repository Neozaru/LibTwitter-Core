#ifndef H_CurlProcess_H
#define H_CurlProcess_H



#include <pthread.h>

#include "curl/curl.h"

#include <string>
#include <iostream>
#include <map>


/**
* \class CurlProcess CurlProcess.h
*
* \brief This class uses libcURL for making and sending web HTTP requests, and get responses.
*/
class CurlProcess {
public:

	/**
	* \fn CurlProcess
	* \brief Contructor. An URL can be passed directly in constructor.
	*
	* \param url Optional URL target for the request. If not defined, 
	* an URL MUST BE defined before sending, via set_URL(url)
	*
	*/
	CurlProcess( const std::string& url = "" );
	
	/**
	* \fn ~CurlProcess
	* \brief Destructor. Eliminates object and closes libcURL connection,
	*
	*/
	~CurlProcess();

	/**
	* \fn set_URL
	* \brief Defines the target URL of the HTTP request
	*
	* \param url URL, without get data ("?[...]&...")
	*/
	void set_URL( const std::string& url );

	/**
	* \fn get_URL
	* \brief Gets the target URL of the HTTP request
	*
	* \return Target URL, without get or POST data.
	*/
	const std::string& get_URL();

	/**
	* \fn add_GET_parameter
	* \brief Adds GET data to HTTP request
	*
	* \param key Left member of data (<key>=...)
	* \param value Right member of data (...=<Value>)
	*
	* If only Key is specified, data will be stored without "=" symbol
	*
	* \return true if data was added successfully, false otherwise (bad key)
	*
	*/
	bool add_GET_parameter( const std::string& key, const std::string& value = "" );
	
	/**
	* \fn add_POST_parameter
	* \brief Adds POST data to HTTP request
	*
	* \param key Left member of data (<key>=...)
	* \param value Right member of data (...=<Value>)
	*
	* If only Key is specified, data will be stored without "=" symbol
	*
	* \return true if data was added successfully, false otherwise (bad key)
	*
	*/
	bool add_POST_parameter( const std::string& key, const std::string& value = "" );

	/**
	* \fn set_GET_data
	* \brief Sets GET data of HTTP request. Erease all other GET data.
	*
	* \param data An std::map conainting <keys,values> data
	*/
	void set_GET_data( const std::map<std::string,std::string>& data );

	/**
	* \fn set_POST_data
	* \brief Sets POSTS data of HTTP request. Erease all other POST data.
	*
	* \param data An std::map conainting <keys,values> data
	*/
	void set_POST_data( const std::map<std::string,std::string>& data );

	/**
	* \fn add_form_file
	* \brief Adds a file in multipart upload list. (ex : uploading an image with status)
	*
	* \param field_name Name of the form field
	* \param file_path Path to the file to upload
	*
	*/
	void add_form_file( const std::string& field_name, const std::string& file_path );

	/**
	* \fn add_form_data
	* \brief Adds data to a HTTP multipart form. Replaces "POST" data in uploading requests
	*
	* \param field_name Name of the form field
	* \param value Associated data
	*
	*/
	void add_form_data( const std::string& field_name, const std::string& value );


	/**
	* \fn send
	* \brief Sends request to target URL. This is a blocking method.
	*/
	void send();

	/**
	* \fn send_async
	* \brief Sends request to target URL. Non-blocking equivalent to "send()"
	*
	* \return 0 if request was successfully sent, thread error code otherwise (TODO)
	*/
	int send_async();

	/**
	* \fn stop
	* \brief Cancel request, and close connection if open. Only async requests are concerned.
	*
	* \return 0 if request was sucessfully aborted, thread error code otherwise (TODO)
	*/
	int stop();

	/**
	* \fn is_running
	* \biref Check if communication is in process
	*
	* \return true if communication is in process, false otherwise
	*/
	bool is_running() const;

	/**
	* \fn get_response_code
	* \brief Get response code of the request
	*
	* \return HTTP response code if received, 999 otherwise (TODO)
	*
	*/
	unsigned long get_response_code() const;	

	/**
	* \fn _on_data_received
	* \brief Called automatically when data is received (virtual pure in base Class)
	*
	* \param data Autofilled parameter containing received data
	*/
	virtual void _on_data_received( const std::string& data ) = 0;

	/**
	* \fn _on_connection_closed
	* \brief Called automatically when connection is closed (virtual pure in base Class)
	*
	* \param response_code Autofilled parameter containing received response code
	*/
	virtual void _on_connection_closed( unsigned long response_code ) = 0;

protected:

	/**************/
	/* ATTRIBUTES */
	/**************/

	CURL* _curl;
	struct curl_httppost* _form_post;
	struct curl_httppost* _form_end;
	struct curl_slist* _header_list;

	std::string _url;
	
	bool _running;

	std::map<std::string,std::string> _GET_data;
	std::map<std::string,std::string> _POST_data;

	unsigned long _response_code;


	pthread_t _thread_id;





	/**
	* \fn load_curl
	* \brief Called automatically with Constructor. Loads libcURL objects.
	*
	* \return A cURL object, which will be used for sending HTTP requests and receiving responses.
	*
	*/
	CURL* load_curl();

	/* Will be deported to Utils:: */
	const std::string concatenate_data( const std::map<std::string,std::string>& data_source ) const;
	//bool set_authentification(  const std::string& user, const std::string& password );

	/**
	* \fn prepare
	* \brief Called automatically before sending requests.
	*
	* Subclasses can overload this method in order to automatize some operations
	*
	*/
	virtual void prepare();

};




#endif