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
    }
}
