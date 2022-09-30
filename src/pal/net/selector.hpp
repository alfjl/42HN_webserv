#ifndef WEBSERV_PAL_NET_SELECTOR_HPP
#define WEBSERV_PAL_NET_SELECTOR_HPP

#include "../../defs.hpp"
#include "../../util/connection.hpp"

#include "reactor.hpp"

namespace webserv {
    namespace core {

        class driver;

    };


    namespace pal {
        namespace net {

            class selector {
                typedef reactor*                payload_type;

            private:
                std::map<socket*, payload_type> elements; // socket = registered/active socket
                webserv::core::driver*          the_driver;

            public:
                selector();
                ~selector();

                void register_socket(socket* socket, payload_type data_set);
                void register_socket(socket* socket);
                void unregister_socket(socket *socket);
                void set_driver(webserv::core::driver* driver);

                void select();
            };

        }
    }
}

#endif
