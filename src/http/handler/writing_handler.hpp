#ifndef WEBSERV_HTTP_HANDLER_WRITING_HANDLER_HPP
#define WEBSERV_HTTP_HANDLER_WRITING_HANDLER_HPP

#include "../../defs.hpp"

#include "../../util/connection.hpp"
#include "basic_handler.hpp"

namespace webserv {
    namespace http {

        class writing_handler : public basic_handler {
            std::string  _text;
            unsigned int _index;

        public:
            writing_handler(std::string text, webserv::util::connection* connection);
            ~writing_handler();

            void start();
            
            void done();
            void restart();

            void check_connection();

            void parse_fields();
            void read_chunked_body__parse_hex();
            enum abort_mode abort();
            unsigned int get_normal_body_size();
        };

    }
}

#endif
