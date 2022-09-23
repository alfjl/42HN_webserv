#ifndef WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_HTTP_HANDLER_HPP

#include "../../defs.hpp"

#include "../../core/routing/routing.hpp"
#include "../../util/state_machine.hpp"
#include "../../util/connection.hpp"

namespace webserv {
    namespace http {

        class http_handler : public webserv::util::state_machine<http_handler> {

        private:
            char                        last_char;
            std::string                 buffer;
            webserv::util::connection*  connection;
            webserv::core::routing&     routing;

        public:
            http_handler(webserv::util::connection* new_connection, webserv::core::routing& routing);

            webserv::util::wrapped_queue& in();
            std::ostream& out();

            void wait_for_char();

            void start();

            void replace(std::string& str, const std::string& from, const std::string& to);

            void char_arrived();

        }; // class http_handler

    } // namespace http
} // namespace webserve

#endif
