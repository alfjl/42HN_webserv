#ifndef WEBSERV_HTTP_CGI_CGI_MSG_HPP
#define WEBSERV_HTTP_CGI_CGI_MSG_HPP

#include "../../defs.hpp"

#include "../../core/instance.hpp"
#include "../../pal/fork/fork.hpp"
#include "../../util/binbuf.hpp"

#include "../fields.hpp"
#include "request.hpp"

namespace webserv {
    namespace http {

        class cgi_message {
            std::string                   _method;
            std::string                   _path_translated;
            webserv::util::binary_buffer  _message_body;
            webserv::http::fields         _fields;
            webserv::http::request&       _request;
            webserv::core::instance&      _current_instance;

        public:
            cgi_message(webserv::http::request& request, webserv::core::instance& current_instance, std::string path_translated);
            ~cgi_message();

            fields&                  get_fields();
            webserv::core::instance& get_current_instance();
            const webserv::util::binary_buffer& get_message_body();

            void setup_fields();

            void write_on(std::ostream& o, int infd);
            void put_fields_into_task(webserv::pal::fork::fork_task& task);
        };

    }
}

#endif