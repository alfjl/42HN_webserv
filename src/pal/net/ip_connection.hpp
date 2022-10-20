#ifndef WEBSERV_PAL_NET_IP_CONNECTION_HPP
#define WEBSERV_PAL_NET_IP_CONNECTION_HPP

#include "../../defs.hpp"

#include "ip_address.hpp"

namespace webserv {
    namespace pal {
        namespace net {
            class ip_connection {
                int         _port;
                ip_address  _address;

            public:
                ip_connection(ip_address address, int port);
                ~ip_connection();

                int get_port();
                std::string get_address_s();
            };

        }
    }
}

#endif