#include "Test_Requests.h"

#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>

int main( int argc, char** argv ) {

	if ( argc > 2 ) {

		std::cout << "Test Suite started" << std::endl;

		Test_Requests tester = Test_Requests();
		g_user = argv[1];
		g_pass = argv[2];
		

		if ( argc > 3 ) {
			g_log_file = argv[3];
		}
		else {
			g_log_file = "output.txt";
		}

		bool suite = true;

		if ( suite ) {

			tester.start_tests();

		}
		else {

			CppUnit::TestSuite suite;
			CppUnit::TextTestResult result;
			suite.addTest( new CppUnit::TestCaller<Test_Requests>(
			                       "update_status_test", 
			                       &Test_Requests::update_status_test ) );
		
			suite.run( &result );
			std::cout << result << std::endl;

		}

	}
	else {
		std::cout << "Usage : " << argv[0] << " <username> <password>" << std::endl;
	}

	return 0;
}