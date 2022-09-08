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

        void register_socket(socket *socket, payload_type data_set) {
            
            // TODO: Question:
            // What if the 'socket *' already exists in the map?
            // Throw exception?
            // Is that problematic? Will that even happen in our program?

            the_mutex.lock();
            elements.insert(std::pair<socket *, payload_type>(socket, data_set)); // TODO: Question: 'pair()' or 'new pair()'?
            the_mutex.unlock();

        }

        void unregister_socket(socket *socket) {

            the_mutex.lock();
            elements.erase(socket);
            the_mutex.unlock();

        }

        void select() {}

            int     highest_fd;
            fd_set  readable;
            fd_set  writeable;
            fd_set  except;

            the_mutex.lock();
            // iterate over all sockets and save into readable, writable or expect exception
            std::map<socket *, payload_type>::iterator it = elements.begin();
            std::map<socket *, payload_type>::iterator ite = elements.end();
            for ( ; it != ite; ++it) {
                
            }
            the_mutex.unlock();

            int status = ::select(highest_fd + 1, readable, writabel, except, NULL);
            if (status < 0)
                throw std::runtime_error();
            // TODO: Question:
            // "::select() returns 0 if the time limit expires"
            // catch in same exception as '-1' error, or ignore?
        }

        /* TODO: Adding, removing, selecting, yada yada yada ... */

    };

        }
    }
}

#endif
