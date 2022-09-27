#include "routing.hpp"

namespace webserv {
    namespace core {

        /* ---------------------- ROUTING ----------------------------------- */

        routing::routing(instance& the_inst) : component(the_inst) {

        }

        routing::~routing() {

        }

        webserv::http::http_response* routing::look_up(webserv::http::request_core& request) {
            webserv::http::http_response *response = new webserv::http::http_response();
            response->set_code(200);
            response->set_body("<html><head></head><body>Dies ist ein Text!!!</body></html>");
            return (response);
        }

        void routing::tick() {

        }


        /* ---------------------- ROUTING_TABLE ----------------------------- */

        void add_rule(webserv::http::path in, webserv::http::path out) {
            // TODO: Implement!
        }

        webserv::http::path routing_table::query(webserv::http::path old_path) {
            webserv::http::path queried_path(old_path.get_addr_s());

            // look_up if prefix substitution rule for old_path exist
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
