#ifndef WEBSERV_HTTP_HANDLER_CGI_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_CGI_HANDLER_HPP

#include "../../defs.hpp"

#include "../../core/routing/routing.hpp"
#include "../../util/state_machine.hpp"
#include "../../util/connection.hpp"

namespace webserv {
    namespace http {

        class cgi_handler : public webserv::util::state_machine<cgi_handler> {
            char                        last_char;
            webserv::util::connection*  connection;

        public:
            cgi_handler(webserv::util::connection* new_connection);
            ~cgi_handler();

            webserv::util::wrapped_queue& in();
            std::ostream& out();

            void wait_for_char();

            void start();

            void char_arrived();
        };

    }
}

#endif
