#include <Twitter/Core/TwitterSession.h>

/* In this example, we just extend TwitterSession, which acts as a Listener */
class MyTwitterSession : public TwitterSession {
public:
	MyTwitterSession() {}
	~MyTwitterSession() {}

	/* Overridded from TwitterSession */
	void on_request_data_received( int request_id, const std::string& data ) {

		std::cout << "(Ctrl+C to Quit) | Data from request " << request_id << ": " << data << std::endl; 
		/* ... Your stuff ... */

	}

};