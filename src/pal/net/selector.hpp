#ifndef WEBSERV_PAL_NET_SELECTOR_HPP
#define WEBSERV_PAL_NET_SELECTOR_HPP

#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace net {

    template <typename T>
    class selector {

    private:
        typedef T  payload_type;

    private:
        std::map<socket *, payload_type>    elements; // socket = registered/active socket

    public:
        selector() {}
        ~selector() {}

        void register_socket(socket *socket, payload_type data_set) {
            elements[socket] = data_set;
        }

        void register_socket(socket* socket) {
            elements[socket] = payload_type();
        }

        void unregister_socket(socket *socket) {
            elements.erase(socket); // call function on payload?
        }

        void select() {

            int     highest_fd = -1;
            fd_set  read_fds;
            fd_set  write_fds;
            fd_set  exception_fds;

            FD_ZERO(&read_fds);
            FD_ZERO(&write_fds);
            FD_ZERO(&exception_fds);

            // iterate over all sockets and save into read_fds, writable or expect exception
            typename std::map<socket *, payload_type>::iterator it = elements.begin();
            typename std::map<socket *, payload_type>::iterator ite = elements.end();

            for ( ; it != ite; ++it) {
                if (it->first->is_data_socket()) {
                    FD_SET(it->first->get_fd(), &write_fds);
                }
                FD_SET(it->first->get_fd(), &read_fds);
                FD_SET(it->first->get_fd(), &exception_fds);
                if (it->first->get_fd() > highest_fd) {
                    highest_fd = it->first->get_fd();
                }
            }

            // use ::select() to check all 3 sets
            int status = ::select(highest_fd + 1, &read_fds, &write_fds, &exception_fds, NULL);
            if (status < 0) {// if select() throws error
                throw std::runtime_error("select(...) returned an error code!");
            }

            // iterate over all sockets check, which fd_set they belong to
            // and call corresponding function
            it = elements.begin();
            for ( ; it != ite; ++it) {
                if (FD_ISSET(it->first->get_fd(), &read_fds)) {
                    // do_read_operation(); TODO: What to do with that information?
                    // e.g.: read(it->first.get_fd(), it->second, [which size???]);
                    // or: it->second.read(it->first)
                    std::cout << "Readable " << it->first->get_fd() << "!" << std::endl;
                    if (it->first->is_server_socket()) {
                        data_socket* ds = ((server_socket*) it->first)->accept();
                        register_socket(ds);
                    } else if (it->first->is_data_socket()) {
                        char buffer[128];
                        ssize_t amount = read(((data_socket*) it->first)->get_fd(), buffer, sizeof(buffer));
                        if (amount > 0)
                            write(it->first->get_fd(), buffer, amount);
                        else if (amount <= 0) {
                            std::cout << "Removing socket " << it->first->get_fd() << std::endl;
                            unregister_socket(it->first);
                            it->first->close();
                            break; // Iterator gets invalidated
                        }
                    }
                }
                else if (FD_ISSET(it->first->get_fd(), &write_fds)) {
                    // do_write_operation(); TODO: What to do with that information?
                }
                else if (FD_ISSET(it->first->get_fd(), &exception_fds)) {
                    // do_exception_operation(); TODO: What to do with that information?
                }
            }
        }
    };

        }
    }
}

#endif
