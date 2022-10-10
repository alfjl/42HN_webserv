#ifndef WEBSERV_UTIL_OFLOW_HPP
#define WEBSERV_UTIL_OFLOW_HPP

#include "../defs.hpp"

namespace webserv {
    namespace util {

        class connection;

        class oflow : public std::streambuf {
            connection& con;

        public:
            oflow(connection& _con);
            
            std::streamsize xsputn(const char * s, std::streamsize n);
            int_type overflow(int_type c = traits_type::eof());
        };

        class ofdflow : public std::streambuf {
            int _fd;

        public:
            ofdflow(int fd);
            
            std::streamsize xsputn(const char * s, std::streamsize n);
            int_type overflow(int_type c = traits_type::eof());
        };

    }
}

#endif
