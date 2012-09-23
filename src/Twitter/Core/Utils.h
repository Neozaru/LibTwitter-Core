#ifndef H_TWUTILS_H
  #define H_TWUTILS_H

  #include <stdarg.h>


  #include <vector>
  #include <map>
  #include <string>
  #include <iostream>
  #include <sstream>

	#include <algorithm>

  #include <locale>



  extern bool _g_debug_mode;


  namespace Utils {


    /**
    * \fn debug
    * \brief Simple stdout, but checks if flag "debug_mode" is set before printing.
    */
    void debug( const std::string& str );

    template<typename T>
    const std::string otos( const T& Value );

    std::string put_variable_in_url( const std::string& URL, 
                                     const std::string& var_name, 
                                     const std::string var_value );


    std::vector<std::string> get_variable_names( int count, ... );

    std::map<std::string,std::string> index_variables_key_value( std::vector<std::string> keys, ... );

  };
    

#endif