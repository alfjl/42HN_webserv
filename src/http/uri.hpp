#ifndef WEBSERV_HTTP_URI_HPP
#define WEBSERV_HTTP_URI_HPP

#include "../defs.hpp"

namespace webserv {
    namespace http {

        class path {
        };

        class uri {
            std::string   _proto;
            std::string   _server;
            unsigned int  _port;
            path          _path;
        public:
            uri();
            ~uri();

            std::string get_proto() { return _proto; }
            std::string get_server() { return _server; }
            unsigned int get_port() { return _port; }
            path& get_path() { return _path; }
        };

    }
}

#endif
