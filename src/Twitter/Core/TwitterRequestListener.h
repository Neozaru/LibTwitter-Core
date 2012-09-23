#ifndef H_TWITTER_REQUEST_LISTENER
	#define H_TWITTER_REQUEST_LISTENER

	class TwitterRequest;

	/**
	* \class TwitterRequestListener
	* \brief Interface for event handling. Listeners can be added to TwitterRequest
	*
	* Users have to sublcass this interface and redefine pure virtual methods.
	*
	*/
	class TwitterRequestListener {
		public:

			/**
			* \fn on_request_data_received
			* \brief Called when a request receives new data
			*
			* \param request Concerned TwitterRequest
			* \param data Received data
			*
			*/
			virtual void on_request_data_received( TwitterRequest* request, const std::string& data ) = 0;
			
			/**
			* \fn on_request_connection_closed
			* \brief Called when a request receives new data
			*
			* \param request Concerned TwitterRequest
			*
			*/
			virtual void on_request_connection_closed( TwitterRequest* request, unsigned long response_code ) = 0;
	};

#endif /* H_TWITTER_REQUEST_LISTENER */