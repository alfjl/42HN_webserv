#include "selector.hpp"

#include "../../core/instance.hpp"
#include "../../core/driver/driver.hpp"

namespace webserv {
    namespace pal {
        namespace net {

            selector::selector() {}
            selector::~selector() {}

            void selector::register_socket(socket* socket, payload_type data_set) {
                if (data_set != NULL)
                    data_set->increment_refcount();
                elements[socket] = data_set;
            }

            void selector::register_socket(socket* socket) {
                elements[socket] = payload_type();
            }

            void selector::unregister_socket(socket* sock) {
                std::map<socket*, payload_type>::iterator it = elements.find(sock);
                if (it != elements.end()) {
                    it->first->close();
                    if (it->second != NULL) {
                        it->second->react_close();
                        it->second->decrement_refcount();
                    }
                    elements.erase(it); // TODO: call function on payload?
                }
            }

            void selector::set_driver(webserv::core::driver* driver) {
                the_driver = driver;
            }

            void selector::select() {

                int     highest_fd = -1;
                fd_set  read_fds;
                fd_set  write_fds;
                fd_set  exception_fds;

                FD_ZERO(&read_fds);
                FD_ZERO(&write_fds);
                FD_ZERO(&exception_fds);

                // iterate over all sockets and save into read_fds, writable or expect exception
                std::map<socket*, payload_type>::iterator it = elements.begin();
                std::map<socket*, payload_type>::iterator ite = elements.end();

                for ( ; it != ite; ++it) {
                    if (it->first->is_data_socket() && it->second != NULL && it->second->get_output().has_next()) {
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
                // it = connections.begin();
                for ( ; it != ite; ++it) {
                    if (FD_ISSET(it->first->get_fd(), &read_fds)) {
                        // do_read_operation();
                        if (it->first->is_server_socket()) {
                            data_socket* ds = ((server_socket*) it->first)->accept();
                            // Callback to driver, create new connection
                            webserv::util::connection* new_connection = new webserv::util::connection();// ALF // just a test!
                            register_socket(ds, new_connection); // ALF
                            the_driver->get_instance().pass_connection(new_connection); // ALF
                        } else if (it->first->is_data_socket()) {
                            char buffer[128];
                            ssize_t amount = read(((data_socket*) it->first)->get_fd(), buffer, sizeof(buffer));
                            if (amount > 0) {
                                for (ssize_t index = 0; index < amount; index++)
                                    it->second->get_input().push_char(buffer[index]);
                            } else if (amount <= 0) {
                                unregister_socket(it->first);
                                break; // Iterator gets invalidated
                            }
                        }
                    }
                    else if (FD_ISSET(it->first->get_fd(), &write_fds)) {
                        // TODO: do_write_operation();
                        if (it->first->is_data_socket()) {
                            char buffer[128]; // bis char buffer voll, oder connection zuende, dann ....
                            // output queue nach Inhalt fragen
                            // falls vorhanden, in buffer[128] schreiben (Anzahl mitzaehlen)
                            // entweder output_queue leer, oder buffer voll (0 - 127, kein /0 noetig)
                            // ssize_t amount = write(((data_socket*) it->first)->get_fd(), buffer, sizeof(was im buffer steht/Anzahl));

                            ssize_t amount = 0;
                            while (amount < 128 && it->second->get_output().next_char(buffer[amount])) {
                                amount++;
                            }
                            ssize_t written = write(it->first->get_fd(), buffer, amount);

                            if (written > 0) {
                                while (amount > written) {
                                    amount--;
                                    it->second->get_output().unread_char(buffer[amount]);
                                }
                            } else {
                                // TODO: Print an error and close
                            }
                        }
                    }
                    else if (FD_ISSET(it->first->get_fd(), &exception_fds)) {
                        // do_exception_operation(); TODO: What to do with that information?
                        // react()->close()??????
                        unregister_socket(it->first);
                        break;
                    }
                }

                it = elements.begin();
                while (it != elements.end()) {
                    if (it->second != NULL) {
                        if (it->second->is_closed() && !it->second->get_output().has_next()) {
                            unregister_socket(it->first);
                            it = elements.begin();
                            continue;
                        }
                    }
                    ++it;
                }
            }

        }
    }
}
