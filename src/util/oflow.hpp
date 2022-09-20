#ifndef WEBSERV_UTIL_OFLOW_HPP
#define WEBSERV_UTIL_OFLOW_HPP

#include "../defs.hpp"
#include "connection.hpp"

namespace webserv {
    namespace util {

        class oflow : public std::ostream {
        private:
            connection& con;

        public:
            oflow(connection& _con);
            int_type overflow(int_type c = traits_type::eof());

        };

    }
}

#endif
