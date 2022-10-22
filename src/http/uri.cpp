#include "uri.hpp"

namespace webserv {
    namespace http {

        uri::uri() : _proto("http"), _server(""), _port(80), _path() {

        }

        uri::~uri() {

        }

        std::string& uri::get_proto() { return _proto; }
        std::string& uri::get_server() { return _server; }
        unsigned int& uri::get_port() { return _port; }
        webserv::util::path& uri::get_path() { return _path; }
        fields& uri::get_params() { return _params; }

        const std::string& uri::get_proto() const { return _proto; }
        const std::string& uri::get_server() const { return _server; }
        unsigned int uri::get_port() const { return _port; }
        const webserv::util::path& uri::get_path() const { return _path; }
        const fields& uri::get_params() const { return _params; }

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
