#ifndef WEBSERV_HTTP_URI_HPP
#define WEBSERV_HTTP_URI_HPP

#include "../defs.hpp"

namespace webserv {
    namespace http {

        class path {
            std::string   _addr;

        public:
            path();
            path(std::string addr);
            ~path();

            std::string& get_addr() { return _addr; }
            const std::string& get_addr() const { return _addr; }
        };

        class uri {
            std::string   _proto;
            std::string   _server;
            unsigned int  _port;
            path          _path;
        public:
            uri();
            ~uri();

            std::string& get_proto() { return _proto; }
            std::string& get_server() { return _server; }
            unsigned int& get_port() { return _port; }
            path& get_path() { return _path; }

            const std::string& get_proto() const { return _proto; }
            const std::string& get_server() const { return _server; }
            unsigned int get_port() const { return _port; }
            const path& get_path() const { return _path; }
        };

        std::ostream& operator<<(std::ostream& stream, const uri& the_uri);

    }
}

#endif
