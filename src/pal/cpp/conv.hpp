#ifndef WEBSERV_PAL_CPP_CONV_HPP
#define WEBSERV_PAL_CPP_CONV_HPP

#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace cpp {

            bool is_inbounds_for_int(long val);

            bool string_to_int(const char* text, int& loc);
            bool hex_string_to_uint(std::string _buffer, unsigned int& value);

            std::string int_to_string(unsigned int code);

        }
    }
}

#endif
