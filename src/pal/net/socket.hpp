#ifndef WEBSERV_PAL_SOCKET_SOCKET_HPP
#define WEBSERV_PAL_SOCKET_SOCKET_HPP

#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace net {

    class socket {
        int fd;
    public:
        socket();
        ~socket();

        int get_fd() const { return fd; }
        
        virtual bool is_server_socket() const { return false; }
        virtual bool is_data_socket()   const { return false; }

        /* TODO: Reading, writing, yada yada yada ... */
    };

        }
    }
}

#endif
