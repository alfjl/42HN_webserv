#ifndef WEBSERV_HTTP_URI_HPP
#define WEBSERV_HTTP_URI_HPP

#include "../defs.hpp"
#include "../util/path.hpp"

#include "fields.hpp"

namespace webserv {
    namespace http {

        class uri {
            std::string         _proto;
            std::string         _server;
            unsigned int        _port;
            webserv::util::path _path;
            fields              _params;

        public:
            uri();
            ~uri();

            std::string& get_proto();
            std::string& get_server();
            unsigned int& get_port();
            webserv::util::path& get_path();
            fields& get_params();

            const std::string& get_proto() const;
            const std::string& get_server() const;
            unsigned int get_port() const;
            const webserv::util::path& get_path() const;
            const fields& get_params() const;
        };
        
        std::ostream& operator<<(std::ostream& stream, const uri& the_uri);

    }
}

#endif
