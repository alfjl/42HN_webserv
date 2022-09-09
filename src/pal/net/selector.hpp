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
        mutex                               the_mutex; // do we need a mutex objekt here? '

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

            int     highest_fd = -1;
            fd_set  read_fds;
            fd_set  write_fds;
            fd_set  exception_fds;

            FD_ZERO(&read_fds);
            FD_ZERO(&write_fds);
            FD_ZERO(&exception_fds);

            // ------------------------ 1. loop --------------------------------
            // iterate over all sockets and save into read_fds, writable or expect exception
            std::map<socket *, payload_type>::iterator it = elements.begin();
            std::map<socket *, payload_type>::iterator ite = elements.end();
            the_mutex.lock();
            for ( ; it != ite; ++it) {
                if (it->first.is_data_socket()) {
                    FD_SET(it->first.get_fd(), write_fds);
                }
                FD_SET(it->first.get_fd(), read_fds);
                FD_SET(it->first.get_fd(), exception_fds);
                if (it->first.get_fd() > highest_fd) {
                    highest_fd = it->first.get_fd();
                }
            }
            the_mutex.unlock();
            // ------------------------ 1. loop --------------------------------


            // ------------------------ SELECT CALL ----------------------------
            // use ::select() to check all 3 
            int status = ::select(highest_fd + 1, read_fds, write_fds, exception_fds, NULL);
            if (status < 0) {// if select() throws error
                throw std::runtime_error("select(...) returned an error code!");
            }
            // TODO: Question:
            // "::select() returns 0 if the time limit expires"
            // catch in same exception as '-1' error, or ignore?
            // ------------------------ SELECT CALL ----------------------------


            // ------------------------ 2. loop --------------------------------
            // iterate over all sockets check, which fd_set they belong to
            // and call corresponding function
            it = elements.begin();
            for ( ; it != ite; ++it) {
                if (FD_ISSET(it->first.get_fd(), read_fds)) {
                    // do_read_operation(); TODO: What to do with that information?
                    // e.g.: read(it->first.get_fd(), it->second, [which size???]);
                    // or: it->second.read(it->first)
                }
                else if (FD_ISSET(it->first.get_fd(), write_fds)) {
                    // do_write_operation(); TODO: What to do with that information?
                }
                else if (FD_ISSET(it->first.get_fd(), exception_fds)) {
                    // do_exception_operation(); TODO: What to do with that information?
                }
            }
            // ------------------------ 2. loop --------------------------------
            // TODO: check
            // TODO: think about, if we have to lock or unlock second for loop
        }

        /* TODO: Adding, removing, selecting, yada yada yada ... */

    };

        }
    }
}

#endif
