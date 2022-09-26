#include "request_parser.hpp"

#include "../../pal/cpp/conv.hpp"

namespace webserv {
    namespace http {

        request_parser::request_parser(iflow& flow) : parser(flow) {

        }

        request_parser::~request_parser() {

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


        static bool split_on(std::string text, std::string& in, std::string& left, std::string& right) {
            size_t it = in.find(text);
            if (it != std::string::npos) {
                left  = in.substr(0, it);
                right = in.substr(it + text.size(), in.size());
                return true;
            }
            return false;
        }

        bool parse_uri(std::string text, uri& into) {
            split_on("://", text, into.get_proto(), text);
            std::string addr;

            if (split_on("/", text, addr, text)) {
                // We lost the "/", so we just add it again
                text = "/" + text;
            } else {
                addr = text;
                text = "/";
            }

            {
                std::string num;
                int         loc;

                if (split_on(":", addr, into.get_server(), num)) {
                    if (!webserv::pal::cpp::string_to_int(num.c_str(), loc)) {
                        return false;
                    }
                    into.get_port() = loc;
                } else {
                    into.get_server() = addr;
                }
            }

            // should path.addr remain "/" as our default, or change to "[empty string]"
            // into.get_path() = path(text);
            
            // while (split_on()) {

            // }
            into.get_path() = path(text);

            return true;
        }

        void parse_http_version(request_parser& parser, http_version& into) {
            parser.expects("HTTP/1.1");
        }

        void parse_http_request_line(request_parser& parser, request_line& line) {
                 if (parser.checks("GET"))    line.set_method(http_method_get);
            else if (parser.checks("POST"))   line.set_method(http_method_post);
            else if (parser.checks("DELETE")) line.set_method(http_method_delete);
            else /* TODO: Error */;

            parser.expect_space();

            {
                std::string uri_text;

                while (!parser.check_space()) {
                    uri_text += parser.force_next_char();
                }

                parse_uri(uri_text, line.get_uri());
            }
            // TODO: Extract until space, then: parse_uri(the_text, line.get_uri());

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

