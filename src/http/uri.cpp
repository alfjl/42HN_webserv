#include "uri.hpp"

namespace webserv {
    namespace http {

        path::path() {

        }

        path::path(std::string addr) {

        }

        path::~path() {

        }
        

        uri::uri() : _proto("http"), _server(""), _port(80), _path() {

        }

        uri::~uri() {

        }

        std::ostream& operator<<(std::ostream& stream, const uri& the_uri) {
            stream << the_uri.get_proto() << " | " << the_uri.get_server() << " | " << the_uri.get_port() << " | (TODO: Path)";
            return stream;
        }
    }
}
