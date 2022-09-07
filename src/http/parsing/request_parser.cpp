#include "request_parser.hpp"

namespace webserv {
    namespace http {

        request_parser::request_parser(iflow& flow) : parser(flow) {

        }

        request_parser::~request_parser() {

        }

        /*
         * This function checks for HTTP newlines, that is "\r\n".
         * If one of these gets detected, `true` gets returned and
         * the newline is consumed by the reader.
         * 
         * FEATURE: Maybe add a configuration option to support
         *          combinations like "\n" as a newline as well?
         */
        bool request_parser::check_http_newline() {
            return checks("\r\n");
        }




        void parse_http_request_line(request_parser& parser, request_line& line) {
                 if (parser.checks("GET"))    line.set_method(http_method_get);
            else if (parser.checks("POST"))   line.set_method(http_method_post);
            else if (parser.checks("DELETE")) line.set_method(http_method_delete);
            else /* TODO: Error */;
        }

        void parse_http_request_core(request_parser& parser, request_core& into) {
            parse_http_request_line(parser, into.get_line());
        }

    }
}

