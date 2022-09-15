#ifndef WEBSERV_PAL_NET_SELECTOR_HPP
#define WEBSERV_PAL_NET_SELECTOR_HPP

#include "../../defs.hpp"
#include "reactor.hpp"

namespace webserv {
    namespace pal {
        namespace net {

    class selector {

    private:
        typedef reactor*  payload_type;

    private:
        std::map<socket*, payload_type>    elements; // socket = registered/active socket

    public:
        selector();
        ~selector();

        void register_socket(socket* socket, payload_type data_set);
        void register_socket(socket* socket);
        void unregister_socket(socket *socket);

        void select();

    }; // class selector

        } // namespace net
    } // namespace pal
} // namespace webserv

#endif
