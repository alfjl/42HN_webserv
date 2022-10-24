#include "ip_address.hpp"

namespace webserv {
    namespace pal {
        namespace net {

            ip_address::ip_address(uint32_t address) : _ip_32(address) {

            }

            ip_address::~ip_address() {

            }

            std::string ip_address::get_ip_s() {
                uint8_t octet[4] = {0, 0, 0, 0}; // = unsigned char (assumption)
                std::stringstream ipAddressFinal;

                if (_ip_32) {
                    for (int i = 0 ; i < 4 ; i++) {
                        octet[i] = (_ip_32 >> (i * 8))  & (uint8_t) - 1;
                    }
                    ipAddressFinal << (int)octet[3] << "." << (int)octet[2] << "." << (int)octet[1] << "." << (int)octet[0];
                }
                return ipAddressFinal.str();
            }

            uint32_t    ip_address::get_ip_uint32() {
                return _ip_32;
            }

        }
    }
}
