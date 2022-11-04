#include "request_parser.hpp"

#include "../../pal/cpp/conv.hpp"

#define EVIL 1 // TODO: Implement in comfig

namespace webserv {
    namespace http {

        request_parser::request_parser(iflow& flow) : parser(flow) {

        }

        request_parser::~request_parser() {

        }

        bool request_parser::check_space_noadvance() {
            return check_noadvance(' ');
        }

        bool request_parser::check_space() {
            return check(' ');
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

        static std::string parse_uri_field_word(request_parser& parser) {
            std::string word;
            while (parser.has_next()) {
                if (parser.check_space_noadvance()) break;
                else if (parser.check_noadvance('=')) break;
                else if (parser.check_noadvance('&')) break;
                else word += parser.force_next_char();
            }
            return word;
        }

        static void parse_uri_field(request_parser& parser, fields& into) {
            /*
             * TODO: Check for length
             */
            std::string key = parse_uri_field_word(parser);
            parser.expect('=');
            std::string value = parse_uri_field_word(parser);
            into.put(key, value);
        }

        void parse_uri_fields(request_parser& parser, fields& into) {
            do {
                parse_uri_field(parser, into);
            } while (!parser.check_space() && parser.check('&'));
        }

        void parse_uri(request_parser& parser, uri& into) {
            into.get_proto() = "http";

            if (parser.checks("http://")) {
                // We do nothing here
            }

            if (!parser.check_noadvance('/')) {
                std::string server_name;

                while (parser.has_next()) {
                    if (parser.check_noadvance('/')) {
                        break;
                    } else if (parser.check(':')) {
                        into.get_port() = parser.expect_uint();
                        break;
                    } else if (parser.check_noadvance('?')) {
                        break;
                    } else if (parser.check_space()) {
                        return;
                    }
                    server_name += parser.force_next_char();
                }

                into.get_server() = server_name;
            }

            if (parser.check_noadvance('/')) {
                std::string path;

                while (parser.has_next()) {
                    // TODO: "?p1=v1&p2=v2"
                    if (parser.check_space()) {
                        break;
                    } else if (parser.check('?')) {
                        parse_uri_fields(parser, into.get_params());
                        break;
                    }
                    path += parser.force_next_char();
                }

                into.get_path() = webserv::util::path(path);
            }
        }

        void parse_http_version(request_parser& parser, http_version& into) {
            (void) into;
            parser.expects("HTTP/1.1");
        }

        void parse_http_request_line(request_parser& parser, request_line& line) {
                 if (parser.checks("GET"))    line.set_method(http_method_get);
            else if (parser.checks("POST"))   line.set_method(http_method_post);
            else if (parser.checks("PUT"))    line.set_method(http_method_put);
            else if (parser.checks("DELETE")) line.set_method(http_method_delete);
            else if (parser.checks("HEAD"))   line.set_method(http_method_head);
            else                              parser.parse_error("Expected a valid method!");

            parser.expect_space();

            parse_uri(parser, line.get_uri());

            // TODO: Extract until space, then: parse_uri(the_text, line.get_uri());

            parse_http_version(parser, line.get_version());

            parser.expect_http_newline();
        }

        std::string trim(std::string str) {
            // std::string::iterator ite = str.end();
            // std::string::iterator it = str.begin();
            // std::string           new_string;      

            // // von hinten durch string gehen,
            // for (; ite != it; --ite) {
            //     if (!isspace(ite))
            //         break ;
            // }

            // new_string.assign(it, ite);

            // return new_string;

        //--------------------------

            // const std::string WHITESPACE = " \n\r\t\f\v";

            // size_t start = str.find_first_not_of(WHITESPACE);
            // size_t end = str.find_last_not_of(WHITESPACE);
        
            // size_t len = end - start;
            // return (str.substr(start, len + 1));
        
        //--------------------------
        
            const std::string WHITESPACE = " \n\r\t\f\v";

            size_t start = str.find_first_not_of(WHITESPACE);
            str.substr(start);
            size_t end = str.find_last_not_of(WHITESPACE);
            str.substr(0, end + 1);

            return (str); 
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
                // into.put((EVIL ? trim(key) : key), value);
            }
        }

        void parse_http_request_core(request_parser& parser, request& into) {
            parse_http_request_line(parser, into.get_line());
            parse_request_fields(parser, into.get_fields());
        }

    }
}

