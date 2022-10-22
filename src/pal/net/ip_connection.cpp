#include "ip_connection.hpp"

namespace webserv {
    namespace pal {
        namespace net {

            ip_connection::ip_connection(ip_address address, int port) : _port(port), _address(address) {

            }

            ip_connection::~ip_connection() {

            }


            uint16_t ip_connection::get_port() {
                return _port;
            }

            std::string ip_connection::get_address_s() {
                // TODO: Convert _address into string (e.g "169.544.19")
                return "";
            }

        }
    }
}
