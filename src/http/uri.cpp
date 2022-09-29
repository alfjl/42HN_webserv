#include "uri.hpp"

namespace webserv {
    namespace http {

        uri::uri() : _proto("http"), _server(""), _port(80), _path() {

        }

        uri::~uri() {

        }

        std::ostream& operator<<(std::ostream& stream, const uri& the_uri) {
            stream << the_uri.get_proto() << " | " << the_uri.get_server() << " | " << the_uri.get_port() << " | /" << the_uri.get_path() << " | ";
            fields::const_iterator it = the_uri.get_params().begin();
            while (it != the_uri.get_params().end()) {
                std::cout << (*it).first << "=" << (*it).second << ' ';
                ++it;
            }
            return stream;
        }
    }
}
