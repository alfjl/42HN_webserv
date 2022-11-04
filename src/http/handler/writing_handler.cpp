#include "writing_handler.hpp"


namespace webserv {
    namespace http {

        writing_handler::writing_handler(webserv::util::connection* connection, std::string text) : basic_handler(connection), _text(text) {

        }

        writing_handler::~writing_handler() {

        }

    }
}