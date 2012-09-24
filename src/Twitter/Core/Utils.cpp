#include "Utils.h"

#include "TwitterSession.h"




namespace Utils {

 
  void debug( const std::string& str ) {

      if ( _g_debug_mode) {

        std::cout << str << std::endl;

      }

    }




  std::string put_variable_in_url( const std::string& URL, 
                                   const std::string& var_name, 
                                   const std::string var_value ) {

    std::string pattern = ":"+var_name;
    std::string new_URL(URL);

    size_t found = URL.find(pattern);

    if ( found != std::string::npos ) {
      new_URL.replace(found,var_value.length(),var_value);
    }

    return new_URL;

  }

    std::map<std::string,std::string> index_variables_key_value( std::vector<std::string> keys, ... ) {
      
      std::map<std::string,std::string> parameters;

      va_list list;

      Utils::debug("Args :");

      va_start(list,keys); 
      for( int i=0; i<keys.size(); i++) {

        char* c_str_value = va_arg(list,char*);
        std::string str_value(c_str_value);

        if ( str_value.size() > 0 ) {

          Utils::debug( "'"+keys.at(i)+"'" + " = " + + "'"+ str_value + "'");

          parameters[keys.at(i)] = str_value;
        }

      }

      va_end(list); 

      return parameters;

    }

       std::vector<std::string> get_variable_names( int count, ... ) {

      std::vector<std::string> vect;

      va_list list;
      va_start(list,count);

      for ( int i=0; i<count; i++ ) {
        char* c_str_value = va_arg(list,char*);
        std::string str_value(c_str_value);
        vect.push_back(str_value);
      }

      va_end(list); 

      return vect;

    }



};