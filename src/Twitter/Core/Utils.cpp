#include "Utils.h"

#include "TwitterSession.h"
#include "Utils/urlencode.h"



namespace Utils {

 
  void debug( const std::string& str, char debug_mode ) {

      if ( debug_mode <= NONE || debug_mode > NB_DEBUG_LEVELS ) {
        return;
      }

      const char* str_debug_levels[] {
        "NONE",
        "DEBUG",
        "WARNING",
        "ERROR"
      };

      if ( _g_debug_mode >= debug_mode ) {

        std::cout << "[TwCore : " << str_debug_levels[debug_mode] << "] " << str << std::endl;

      }

    }


  bool replace(std::string& str, const std::string& from, const std::string& to) {
      size_t start_pos = str.find(from);
      if(start_pos == std::string::npos) {
          return false;
      }
      str.replace(start_pos, from.length(), to);
      return true;
  }


  std::string put_variable_in_url( const std::string& URL, 
                                   const std::string& var_name, 
                                   const std::string var_value ) {

    std::string pattern = ":"+var_name;
    std::string new_URL(URL);
    replace(new_URL,pattern,var_value);

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

          parameters[keys.at(i)] = urlencode(str_value);
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