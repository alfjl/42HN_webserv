#ifndef WEBSERV_PAL_SOCKET_SELECTOR_HPP
#define WEBSERV_PAL_SOCKET_SELECTOR_HPP

#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace net {

    template <typename T>
    class selector {

    private:
        typedef T*  payload_type;

    private:
        std::map<socket *, payload_type>    elements; // socket = registered/active socket

    public:
        selector();
        ~selector();

        void register_socket(socket *socket, payload_type data_set);
        void unregister_socket(socket *socket);
        void select();

        /* TODO: Adding, removing, selecting, yada yada yada ... */

    };

        }
    }
}

#endif
