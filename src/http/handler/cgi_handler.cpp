#include "cgi_handler.hpp"

#include "../../core/routing/routing.hpp"
#include "../../pal/cpp/conv.hpp"
#include "../../util/streamflow.hpp"
#include "../parsing/request_parser.hpp"
#include "../response.hpp"

namespace webserv {
    namespace http {

        cgi_handler::cgi_handler(webserv::util::connection* new_connection)
            : connection(new_connection) {
            if (connection != NULL)
                connection->increment_refcount();
        }

        cgi_handler::~cgi_handler() {
            if (connection != NULL)
                connection->decrement_refcount();
        }

        webserv::util::wrapped_queue& cgi_handler::in() { return connection->get_input(); }
        std::ostream& cgi_handler::out() { return connection->get_ostream(); }

        void cgi_handler::wait_for_char() {
            if (in().has_next()) {
                if (in().next_char(last_char)) {
                    ret();
                    return;
                }
            }
            if (connection->is_closed())
                stop();
            else
                yield();
        }

        void cgi_handler::start() {
            next(&cgi_handler::wait_for_char);
            later(&cgi_handler::char_arrived);
        }

        void cgi_handler::char_arrived() {
            std::cerr << "\033[35m" << last_char << "\033[0m";
            next(&cgi_handler::start);
        }

    }
}
