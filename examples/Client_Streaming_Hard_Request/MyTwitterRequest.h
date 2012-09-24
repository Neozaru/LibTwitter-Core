#include <Twitter/Core/TwitterRequest.h>

class MyTwitterRequest : public TwitterRequest {
public:
	MyTwitterRequest( TwitterSession* session, const std::string& url = "") : TwitterRequest(session,url) {}
 
	~MyTwitterRequest() {}

	void on_data_received( const std::string& data ) { 
		std::cout << "(Ctrl+C to Quit) | Data : " << data << std::endl; 
	}
	
};