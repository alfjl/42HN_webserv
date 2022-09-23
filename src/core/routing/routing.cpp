#include "routing.hpp"

namespace webserv {
    namespace core {

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

    } // namespace core
} // namespace webserv
