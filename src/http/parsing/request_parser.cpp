#include "request_parser.hpp"

namespace webserv {
    namespace http {

        request_parser::request_parser(iflow& flow) : parser(flow) {

        }

        request_parser::~request_parser() {

        }

        void request_parser::expect_space() {
            expect(' ');
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

        void request_parser::expect_http_newline() {
            if (!check_http_newline())
                parse_error("Expected a newline!");
        }



        void parse_uri(request_parser& parser, uri& into) {
            parser.parse_error("Oof. URI can not be parsed right now");
        }

        void parse_http_version(request_parser& parser, http_version& into) {
            parser.parse_error("Oof. Version can not be parsed right now");
            parser.expects("HTTP/1.1");
        }

        void parse_http_request_line(request_parser& parser, request_line& line) {
                 if (parser.checks("GET"))    line.set_method(http_method_get);
            else if (parser.checks("POST"))   line.set_method(http_method_post);
            else if (parser.checks("DELETE")) line.set_method(http_method_delete);
            else /* TODO: Error */;

            parser.expect_space();

            parse_uri(parser, line.get_uri());

            parser.expect_space();

            parse_http_version(parser, line.get_version());

            parser.expect_http_newline();
        }

        void parse_request_fields(request_parser& parser, fields& into) {
            while (!parser.check_http_newline()) {
                std::string key;
                std::string value;

                while (!parser.check(':')) {
                    key += parser.force_next_char();
                }

                parser.skip_spaces();

                while (!parser.check_http_newline()) {
                    value += parser.force_next_char();
                }

                into.put(key, value);
            }
        }

        void parse_http_request_core(request_parser& parser, request_core& into) {
            parse_http_request_line(parser, into.get_line());
            parse_request_fields(parser, into.get_fields());
        }

    }
}

