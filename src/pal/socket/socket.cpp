#include "socket.hpp"

namespace webserv::pal::socket {

    socket::socket() {
        fd = -1;
    }

    socket::~socket() {
        if (fd >= 0)
            close(fd);
    }

}
