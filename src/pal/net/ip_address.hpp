#ifndef WEBSERV_PAL_NET_IP_ADDRESS_HPP
#define WEBSERV_PAL_NET_IP_ADDRESS_HPP

#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace net {
            class ip_address {
                uint32_t     _ip_32;

            public:
                ip_address(uint32_t address);
                ~ip_address();

                std::string get_ip_s();
                uint32_t    get_ip_uint32();
            };

        }
    }
}

#endif