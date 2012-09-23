#ifndef H_PIN_PAGE_PARSER_H
	#define H_PIN_PAGE_PARSER_H

	#include "HTML_Parser.h"

	class PIN_Page_Parser : public HTML_Parser {
	public:
		PIN_Page_Parser();
		~PIN_Page_Parser();

		bool parse_page( const std::string& pin_page );

		std::string get_PIN_code();

	private:

		std::string _pin_code;
	};

#endif