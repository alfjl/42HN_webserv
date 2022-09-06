#ifndef WEBSERV_HTTP_REQUEST_PARSER_HPP
#define WEBSERV_HTTP_REQUEST_PARSER_HPP

#include "../util/parser.hpp"

namespace webserv {
    namespace http {

        class request_parser : public webserv::util::parser {
        private:
        public:
            request_parser(iflow& flow);
            ~request_parser();

            bool check_http_newline();
        };

    }
}

#endif
