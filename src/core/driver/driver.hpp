#ifndef WEBSERV_CORE_DRIVER_DRIVER_HPP
#define WEBSERV_CORE_DRIVER_DRIVER_HPP

#include "../component.hpp"
#include "../../pal/net/socket.hpp"
#include "../../pal/net/selector.hpp"

namespace webserv {
    namespace core {

        class driver : public component {
            webserv::pal::net::selector selector;
        
        public:
            driver(instance& the_inst);
            ~driver();

            void open_port(int port);
            void tick();
        };
    }
}

#endif