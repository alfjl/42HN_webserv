#include "routing.hpp"

namespace webserv {
    namespace core {

        routing::routing(instance& the_inst) : component(the_inst) {

        }

        routing::~routing() {

        }

        webserv::http::http_response* routing::look_up(webserv::http::request_core& request) {
            webserv::http::http_response *response = new webserv::http::http_response(request);
            return (response);
        }

        void routing::tick() {

                //TODO
            }

    } // namespace core
} // namespace webserv
