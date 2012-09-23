#ifndef H_HTMLPARSER_H
	#define H_HTMLPARSER_H

	#include <string>

	class HTML_Parser {

	public:
		HTML_Parser() {}
		~HTML_Parser() {}

		virtual bool parse_page( const std::string& html_page ) = 0;


	};

#endif