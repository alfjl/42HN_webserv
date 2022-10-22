#ifndef WEBSERV_UTIL_NOTIFICATION_HPP
#define WEBSERV_UTIL_NOTIFICATION_HPP

#include "../defs.hpp"

#include "../pal/net/reactor.hpp"

#include "iflow.hpp"

namespace webserv {
    namespace util {

        class notification {
            bool  closed;

        public:
            notification();

            void close();
            bool is_closed();

            void react_close();
        };

    }
}

#endif
