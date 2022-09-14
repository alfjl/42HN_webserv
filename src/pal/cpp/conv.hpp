#ifndef WEBSERV_PAL_CPP_CONV_HPP
#define WEBSERV_PAL_CPP_CONV_HPP

namespace webserv {
    namespace pal {
        namespace cpp {

            bool is_inbounds_for_int(long val);

            bool string_to_int(const char* text, int& loc);

        }
    }
}

#endif
