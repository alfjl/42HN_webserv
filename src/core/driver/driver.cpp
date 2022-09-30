#include "driver.hpp"

namespace webserv {
    namespace core {

        driver::driver(instance& the_inst) : component(the_inst) {
            selector.set_driver(this);
        }

        driver::~driver() {

        }

        void driver::open_port(int port) {
            webserv::pal::net::server_socket* sock = new webserv::pal::net::server_socket();

            sock->set_reuseaddr();
            sock->bind(port);
            sock->listen();

            selector.register_socket(sock);
        }

        void driver::tick() {
            selector.select();
            selector.set_driver(this);
        }

    }
}
