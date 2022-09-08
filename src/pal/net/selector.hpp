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
        

    public:
        selector();
        ~selector();

        /* TODO: Adding, removing, selecting, yada yada yada ... */

    };

        }
    }
}

#endif
