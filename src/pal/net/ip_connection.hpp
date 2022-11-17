#ifndef WEBSERV_PAL_NET_IP_CONNECTION_HPP
#define WEBSERV_PAL_NET_IP_CONNECTION_HPP

#include "../../defs.hpp"

#include "ip_address.hpp"

namespace webserv {
    namespace pal {
        namespace net {
            class ip_connection {
                uint16_t    _port;
                ip_address  _address;

            public:
                ip_connection();
                ip_connection(ip_address address, int port);
                ~ip_connection();

                uint16_t get_port();
                std::string get_address_s();
                uint32_t get_address_uint32();
            };

        }
    }
}

#endif