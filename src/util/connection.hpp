#ifndef WEBSERV_UTIL_CONNECTION_HPP
#define WEBSERV_UTIL_CONNECTION_HPP

#include "../defs.hpp"

#include "iflow.hpp"
#include "../pal/net/reactor.hpp"

namespace webserv {
    namespace util {

        class connection : public iflow, public webserv::pal::net::reactor {
        private:
            std::queue<char>  buffer;
            bool              closed;
            std::ostream      the_ostream; // ALF2

        public:
            connection();

            void push_char(char c);

            bool has_next();
            bool next_char(char& loc);

            void close();
            bool is_closed();

            void react_close();

            std::ostream& get_stream(); // ALF2

        }; // class connection

    } // namespace util
} // namespace webserv

#endif