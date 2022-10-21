#include "ip_address.hpp"

namespace webserv {
    namespace pal {
        namespace net {

            ip_address::ip_address(uint32_t address) : _ip_32(address) {

            }

            ip_address::~ip_address() {

            }


            std::string ip_address::get_ip_s() {
                // TODO: Convert _ip_32 to string
            }

            uint32_t    ip_address::get_ip_uint32() {
                return _ip_32;
            }

        }
    }
}
