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
        void add_rule(std::string a, std::string b) {
            // TODO: Implement!
        }

        webserv::http::path routing_table::query(webserv::http::path old_path) {
            webserv::http::path queried_path;
            
            return queried_path;
        }


    } // namespace core
} // namespace webserv
