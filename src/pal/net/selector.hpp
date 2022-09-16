#ifndef WEBSERV_PAL_NET_SELECTOR_HPP
#define WEBSERV_PAL_NET_SELECTOR_HPP

#include "../../defs.hpp"
#include "reactor.hpp"
#include "../../util/notification.hpp" // ALF
#include "../../util/connection.hpp" // ALF
#include "../../core/driver/driver.hpp" // ALF
#include "../../core/instance.hpp" // ALF

namespace webserv {
    namespace pal {
        namespace net {

    class selector {

    private:
        typedef reactor*                        payload_type; // payload_type_1?
        // typedef webserv::util::notification*    payload_type_2; // ALF

    private:
        std::map<socket*, payload_type> elements; // socket = registered/active socket
        // std::map<socket*, payload_type_2>    connections; // socket = registered/active socket
        webserv::core::driver*          the_driver; // ALF

    public:
        selector();
        ~selector();

        void register_socket(socket* socket, payload_type data_set);
        void register_socket(socket* socket);
        void unregister_socket(socket *socket);
        void set_driver(webserv::core::driver* driver) { the_driver = driver; } // ALF //; spaeter auslagern

        void select();

    }; // class selector

        } // namespace net
    } // namespace pal
} // namespace webserv

#endif
