#include <iostream>

#include <Twitter/Core/TwitterRequestListener.h>

class MyRequestListener : public TwitterRequestListener {
public:
	MyRequestListener() {}
	~MyRequestListener() {}

	void on_request_data_received( TwitterRequest* request, const std::string& data ) {

		std::cout << "(Ctrl+C to Quit) | (myListener) Data received : " << data << std::endl; 
		/* ... Your stuff ... */
	}

	void on_request_connection_closed( TwitterRequest* request, unsigned long response_code ) {

		std::cout << "(myListener) Connection closed. (" << response_code << ")" << std::endl;

	}


};