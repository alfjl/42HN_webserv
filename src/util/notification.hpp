#ifndef WEBSERV_UTIL_NOTIFICATION_HPP
#define WEBSERV_UTIL_NOTIFICATION_HPP

#include "../defs.hpp"

#include "iflow.hpp"
#include "../pal/net/reactor.hpp"

namespace webserv {
    namespace util {

        class notification {
        private:
            // connection   in;
            bool              closed;

        public:
            notification();

            void close();
            bool is_closed();

            void react_close();

        }; // class notification

    } // namespace util
} // namespace webserv

#endif