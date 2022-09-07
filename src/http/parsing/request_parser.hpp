#ifndef WEBSERV_HTTP_PARSING_REQUEST_PARSER_HPP
#define WEBSERV_HTTP_PARSING_REQUEST_PARSER_HPP

#include "../../util/parser.hpp"
#include "../request.hpp"

namespace webserv {
    namespace http {

        class request_parser : public webserv::util::parser {
        private:
        public:
            request_parser(iflow& flow);
            ~request_parser();

            bool check_http_newline();
        };

        void parse_http_request_core(request_parser& parser, request_core& into);

    }
}

#endif
