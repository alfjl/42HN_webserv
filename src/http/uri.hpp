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

            std::string& get_proto() { return _proto; }
            std::string& get_server() { return _server; }
            unsigned int& get_port() { return _port; }
            webserv::util::path& get_path() { return _path; }
            fields& get_params() { return _params; }

            const std::string& get_proto() const { return _proto; }
            const std::string& get_server() const { return _server; }
            unsigned int get_port() const { return _port; }
            const webserv::util::path& get_path() const { return _path; }
            const fields& get_params() const { return _params; }
        
        }; // class uri
        
        std::ostream& operator<<(std::ostream& stream, const uri& the_uri);

    } // namespace http
} // namespace webserv

#endif
