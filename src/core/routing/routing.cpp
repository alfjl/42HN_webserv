#include "routing.hpp"

namespace webserv {
    namespace core {

        routing::routing(instance& the_inst) : component(the_inst) {
            selector.set_driver(this);
        }

        routing::~routing() {

        }

        void routing::open_port(int port) {
            webserv::pal::net::server_socket* sock = new webserv::pal::net::server_socket();

            sock->set_reuseaddr();
            sock->bind(port);
            sock->listen();

            selector.register_socket(sock);
        }

        void routing::tick() {
            selector.select();
            selector.set_driver(this); // ALF
        }

    } // namespace core
} // namespace webserv
