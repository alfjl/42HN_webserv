#ifndef WEBSERV_CORE_DRIVER_DRIVER_HPP
#define WEBSERV_CORE_DRIVER_DRIVER_HPP

#include "../component.hpp"

#include "../../pal/net/socket.hpp"
#include "../../pal/net/selector.hpp"

namespace webserv {
    namespace core {

        class   webservs;
        class   selector;

        class driver : public webserv::util::component<webservs> {
            webserv::pal::net::selector selector;
        
        public:
            driver(webservs& the_inst);
            ~driver();

            webserv::util::connection* add_fd(int fd);

            void open_port(int port, instance& the_inst); // TODO: also takes a reference to the instance/routing table the port will be connected to
            void tick();
        };

    }
}

#endif
