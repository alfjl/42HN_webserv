#ifndef WEBSERV_HTTP_CGI_CGI_MSG_HPP
#define WEBSERV_HTTP_CGI_CGI_MSG_HPP

#include "../../defs.hpp"

#include "../../core/instance.hpp"

#include "../fields.hpp"
#include "request.hpp"

namespace webserv {
    namespace http {

        class cgi_message {
            std::string                  _method;
            std::string                  _message_body;
            std::string                  _path_translated;
            webserv::http::fields        _fields;
            webserv::http::request&      _request;
            webserv::core::instance&     _current_instance;

        public:
            cgi_message(webserv::http::request& request, webserv::core::instance& current_instance, std::string path_translated);
            ~cgi_message();

            fields& get_fields();
            webserv::core::instance& get_current_instance();

            void setup_fields();

            void write_on(std::ostream& o);
        };

    }
}

#endif