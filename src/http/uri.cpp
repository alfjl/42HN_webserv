#include "uri.hpp"

namespace webserv {
    namespace http {

        uri::uri() : _proto("http"), _server(""), _port(80), _path() {

        }

        uri::~uri() {

        }
    }
}
