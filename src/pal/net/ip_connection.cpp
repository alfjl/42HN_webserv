#include "ip_connection.hpp"

namespace webserv {
    namespace pal {
        namespace net {

            ip_connection::ip_connection() : _port(), _address() {

            }

            ip_connection::ip_connection(ip_address address, int port) : _port(port), _address(address) {

            }

            ip_connection::~ip_connection() {

            }


            uint16_t ip_connection::get_port() {
                return _port;
            }

            std::string ip_connection::get_address_s() {
                return _address.get_ip_s();
            }

            uint32_t ip_connection::get_address_uint32() {
                return _address.get_ip_uint32();
            }

        }
    }
}
