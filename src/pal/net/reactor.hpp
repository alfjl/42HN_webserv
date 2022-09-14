#ifndef WEBSERV_PAL_NET_REACTOR_HPP
#define WEBSERV_PAL_NET_REACTOR_HPP

#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace net {

            class reactor {

            public:
                virtual void react_close() = 0;
                virtual void push_char(char c) = 0;

            }; // class reactor

        } // namespace net
    } // namespace pal
} // namespace webserv

#endif
