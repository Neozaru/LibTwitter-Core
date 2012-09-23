#ifndef H_AUTH_PAGE_PARSER_H
	#define H_AUTH_PAGE_PARSER_H

	#include "HTML_Parser.h"

	class Auth_Page_Parser : public HTML_Parser {
	public:
		Auth_Page_Parser();
		~Auth_Page_Parser();

		bool parse_page( const std::string& auth_page );

		std::string get_token();
		std::string get_auth_token();

	private:

		std::string _token_value;
		std::string _auth_token_value;

	};

#endif