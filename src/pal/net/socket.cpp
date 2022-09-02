#include "socket.hpp"

namespace webserv::pal::net {

    socket::socket() {
        fd = -1;
    }

    socket::~socket() {
        if (fd >= 0)
            close(fd);
    }

}
