#include "selector.hpp"

#include "../../core/instance.hpp"
#include "../../core/driver/driver.hpp"

namespace webserv {
    namespace pal {
        namespace net {

            selector::selector() {}
            selector::~selector() {}

            void selector::register_socket(socket* socket, payload_type data_set) {
                elements[socket] = data_set;
            }

            void selector::register_socket(socket* socket) {
                elements[socket] = payload_type();
            }

            void selector::unregister_socket(socket* socket) {
                elements.erase(socket); // call function on payload?
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
                    if (it->first->is_data_socket()) {
                        // TODO
                        // We disable writability checks in order to make select() block
                        // FD_SET(it->first->get_fd(), &write_fds);
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
                        std::cout << "Readable " << it->first->get_fd() << "!" << std::endl;
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
                                std::cout << "Removing socket " << it->first->get_fd() << std::endl;
                                unregister_socket(it->first);
                                it->first->close();
                                it->second->react_close();
                                break; // Iterator gets invalidated
                            }
                        }
                    }
                    else if (FD_ISSET(it->first->get_fd(), &write_fds)) {
                        std::cout << "Writeable " << it->first->get_fd() << "!" << std::endl;
                        // TODO: do_write_operation();
                        if (it->first->is_data_socket()) {
                            char buffer[128]; // bis char buffer voll, oder connection zuende, dann ....
                            // output queue nach Inhalt fragen
                            // falls vorhanden, in buffer[128] schreiben (Anzahl mitzaehlen)
                            // entweder output_queue leer, oder buffer voll (0 - 127, kein /0 noetig)
                            // ssize_t amount = write(((data_socket*) it->first)->get_fd(), buffer, sizeof(was im buffer steht/Anzahl));

                            if (amount > 0) {
                                for (ssize_t index = 0; index < amount; index++)
                                    it->second->get_output().push_char(buffer[index]);
                            }
                            ssize_t amount = write(((data_socket*) it->first)->get_fd(), buffer, sizeof(buffer));
                        }
                    }
                    else if (FD_ISSET(it->first->get_fd(), &exception_fds)) {
                        // do_exception_operation(); TODO: What to do with that information?
                        // react()->close()??????
                    }
                }
            }

        } // namespace net
    } // namespace pal
} // namespace webserv
