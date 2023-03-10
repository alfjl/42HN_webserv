#include "../webservs.hpp"
#include "../instance.hpp"

#include "driver.hpp"


namespace webserv {
    namespace core {

        driver::driver(webservs& the_inst) : component(the_inst) {
            selector.set_driver(this);
        }

        driver::~driver() {

        }

        webserv::util::connection* driver::add_fd(int fd) {
            return selector.add_fd(fd);
        }

        void driver::open_port(int port, instance& inst) {
            webserv::pal::net::server_socket* sock = new webserv::pal::net::server_socket(inst);

            sock->set_reuseaddr();
            sock->bind(port);
            sock->listen();

            selector.register_socket(sock);
        }

        void driver::tick() {
            selector.select(get_parent().is_busy());
            selector.set_driver(this);
        }

    }
}
