#ifndef WEBSERV_HTTP_PARSING_REQUEST_PARSER_HPP
#define WEBSERV_HTTP_PARSING_REQUEST_PARSER_HPP

#include "../../util/parser.hpp"
#include "../proto/request.hpp"
#include "../uri.hpp"
#include "../fields.hpp"

namespace webserv {
    namespace http {

        class request_parser : public webserv::util::parser {
        public:
            request_parser(iflow& flow);
            ~request_parser();

            bool check_space_noadvance();
            bool check_space();
            void expect_space();

            bool check_http_newline();
            void expect_http_newline();
        };

        void parse_uri_fields(request_parser& parser, fields& into);
        void parse_uri(request_parser& parser, uri& into);
        void parse_http_request_line(request_parser& parser, request_line& line);
        void parse_request_fields(request_parser& parser, fields& into);
        void parse_http_request_core(request_parser& parser, request& into);

    }
}

#endif
