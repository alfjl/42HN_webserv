#include "routing.hpp"

#include "../instance.hpp"

namespace webserv {
    namespace core {

        /* ---------------------- ROUTING ----------------------------------- */

        routing::routing(instance& the_inst) : component(the_inst) {

        }

        routing::~routing() {

        }

        webserv::http::http_response* routing::look_up(webserv::http::request_core& request) {
            webserv::http::http_response *response = new webserv::http::http_response();

            switch (request.get_line().get_method()) {
                // case webserv::http::http_method_options: std::cout << "TODO: case http_method_options:" << std::endl; break;
                case webserv::http::http_method_get: {
                    webserv::core::routing_table table;
                    webserv::http::path file_path = table.query(request.get_line().get_uri().get_path());
                    std::ifstream stream;
                    get_instance().get_fs().open(file_path, stream);
                    std::ostringstream payload;
                    while (!stream.eof()) {
                        char c;
                        stream.get(c);
                        payload << c;
                    }

                    response->set_code(200);
                    response->set_body(payload.str());

                    break;
                }
                // case webserv::http::http_method_head: std::cout << "TODO: case http_method_head:" << std::endl; break;
                case webserv::http::http_method_post: std::cout << "TODO: case http_method_post:" << std::endl;
                // case webserv::http::http_method_put: std::cout << "TODO: case http_method_put:" << std::endl; break;
                case webserv::http::http_method_delete: std::cout << "TODO: case http_method_delete:" << std::endl;
                // case webserv::http::http_method_trace: std::cout << "TODO:case http_method_trace:" << std::endl; break;
                // case webserv::http::http_method_connect: std::cout << "TODO: case http_method_connect:" << std::endl; break;
                default: {
                    response->set_code(404);
                    response->set_body("<html><head></head><body>Error 404!</body></html>");
                    break;
                }
            }
            return (response);
        }

        void routing::tick() {
            // Do nothing!
        }


        /* ---------------------- ROUTING_TABLE ----------------------------- */

        /*
         * Checks if 'in' is already in prefix_rules
         * If yes, only changes the second rule to 'out'
         * If not, adds the whole pair<in, out> to prefix_rules
         */
        void routing_table::add_rule(webserv::http::path in, webserv::http::path out) {
            iterator it = prefix_rules.begin();
            iterator ite = prefix_rules.end();

            for (; it != ite; ++it) {
                if (it->first == in)
                    break;
            }
            if (it != ite) {
                it->second = out;
            } else {
                prefix_rules.push_back(std::make_pair(in, out));
            }
        }

        /*
         * Checks if prefix of old_path is included in prefix_rules
         * If yes, substitutes the prefix of old_path
         * according to the specific rule set
         */
        webserv::http::path routing_table::query(webserv::http::path old_path) {
            webserv::http::path queried_path(old_path.get_addr_s());

            // look_up if prefix substitution rule for old_path exist
            // and substitute it, if found
            const_iterator it = prefix_rules.begin();
            const_iterator ite = prefix_rules.end();
            for (; it != ite; ++it) {
                if (old_path.begins_with(it->first)) {
                    // change prefix of old_path, according to prefix rule
                    // and save in queried_path
                    queried_path = old_path.adapt_prefix(it->first, it->second);
                    break;
                }
            }
            return queried_path;
        }

    } // namespace core
} // namespace webserv
