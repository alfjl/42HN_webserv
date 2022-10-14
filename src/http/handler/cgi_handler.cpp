#include "cgi_handler.hpp"

namespace webserv {
    namespace http {

        cgi_handler::cgi_handler(webserv::util::connection* new_connection, webserv::http::http_handler* http_handler)
            : basic_handler(new_connection), _http_handler(http_handler) {
                _http_handler->fall_asleep();
        }

        cgi_handler::~cgi_handler() {
            _http_handler->wake_up();
        }

        void cgi_handler::char_arrived() {
            std::cerr << "\033[35m" << basic_handler::get_last_char() << "\033[0m";
            next(&cgi_handler::start);
        }

    }
}
