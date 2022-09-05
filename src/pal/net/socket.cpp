#include "socket.hpp"

namespace webserv {
    namespace pal {
        namespace net {

    socket::socket() {
        fd = -1;
    }

    socket::~socket() {
        if (fd >= 0)
            close(fd);
    }

        }
    }
}
