#include "socket.hpp"

namespace webserv {
    namespace pal {
        namespace net {

    socket::socket() {
        fd = ::socket(PF_INET, SOCK_STREAM, );
    }

    socket::socket(int _fd) {
        fd = _fd;
    }

    socket::~socket() {
        close();
    }

    void socket::close() {
        if (fd >= 0)
            close(fd);
        fd = -1;
    }

        }
    }
}
