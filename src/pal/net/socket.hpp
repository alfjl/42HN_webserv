#ifndef WEBSERV_PAL_SOCKET_SOCKET_HPP
#define WEBSERV_PAL_SOCKET_SOCKET_HPP

#include "../../defs.hpp"

namespace webserv::pal::net {

    class socket {
        int fd;
    public:
        socket();
        ~socket();

        /* TODO: Reading, writing, yada yada yada ... */
    };

}

#endif
