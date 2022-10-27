#include "selector.hpp"

#include "../../core/instance.hpp"
#include "../../core/driver/driver.hpp"

#define WEBSERV_BUFFER_SIZE 32768

namespace webserv {
    namespace pal {
        namespace net {

            selector::selector() {}
            selector::~selector() {}

            void selector::set_driver(webserv::core::driver* driver) {
                the_driver = driver;
            }

            void selector::register_socket(socket* socket, payload_type data_set) {
                socket->increment_refcount();
                if (data_set != NULL)
                    data_set->increment_refcount();
                elements[socket] = data_set;
            }

            void selector::register_socket(socket* socket) {
                socket->increment_refcount();
                elements[socket] = payload_type();
            }

            void selector::unregister_socket(socket* sock) {
                std::map<socket*, payload_type>::iterator it = elements.find(sock);
                if (it != elements.end()) {
                    it->first->close();
                    it->first->decrement_refcount();
                    if (it->second != NULL) {
                        it->second->notify_about_close();
                        it->second->decrement_refcount();
                    }
                    elements.erase(it); // TODO: call function on payload?
                }
            }

            webserv::util::connection* selector::add_fd(int fd) {
                webserv::util::connection* connection = new webserv::util::connection();

                register_socket(new data_socket(fd), connection);

                return connection;
            }

            void selector::error_on_socket(webserv::pal::net::socket* sock) {
                unregister_socket(sock);
            }

            void selector::add_fds(fd_sets& sets) {
                std::map<socket*, payload_type>::iterator it = elements.begin();

                for ( ; it != elements.end(); ++it) {
                    if (it->first->is_data_socket() && it->second != NULL && it->second->get_output().has_next()) {
                        FD_SET(it->first->get_fd(), &sets.write_fds);
                    }
                    FD_SET(it->first->get_fd(), &sets.read_fds);
                    FD_SET(it->first->get_fd(), &sets.exception_fds);
                    if (it->first->get_fd() > sets.highest) {
                        sets.highest = it->first->get_fd();
                    }
                }
            }

            bool selector::process_readable(std::pair<webserv::pal::net::socket*, payload_type> it) {
                if (it.first->is_server_socket()) {
                    data_socket* ds = ((server_socket*) it.first)->accept();
                    webserv::util::connection* new_connection = new webserv::util::connection();
                    register_socket(ds, new_connection);
                    the_driver->get_instance().pass_connection(new_connection);
                } else if (it.first->is_data_socket()) {
                    char buffer[WEBSERV_BUFFER_SIZE];

                    ssize_t amount = read(((data_socket*) it.first)->get_fd(), buffer, sizeof(buffer));

                    if (amount > 0) {
                        for (ssize_t index = 0; index < amount; index++) {
                            it.second->get_input().push_char(buffer[index]);
                        }
                    } else if (amount <= 0) {
                        error_on_socket(it.first);
                        return false;
                    }
                }

                return true;
            }

            bool selector::process_writable(std::pair<webserv::pal::net::socket*, payload_type> it) {
                if (it.first->is_data_socket()) {
                    ssize_t amount = 0;
                    char buffer[WEBSERV_BUFFER_SIZE];

                    while (amount < sizeof(buffer) && it.second->get_output().next_char(buffer[amount])) {
                        amount++;
                    }

                    ssize_t written = write(it.first->get_fd(), buffer, amount);

                    if (written >= 0) {
                        while (amount > written) {
                            amount--;
                            it.second->get_output().unread_char(buffer[amount]);
                        }
                    } else {
                        error_on_socket(it.first);
                        return false;
                    }
                }

                return true;
            }

            bool selector::process_except(std::pair<webserv::pal::net::socket*, payload_type> it) {
                error_on_socket(it.first);
                return false;
            }

            void selector::process_fds(fd_sets& sets) {
                std::map<socket*, payload_type>::iterator it = elements.begin();

                for ( ; it != elements.end(); ++it) {
                    if (FD_ISSET(it->first->get_fd(), &sets.read_fds)) {
                        if (!process_readable(*it)) break;
                    }

                    if (FD_ISSET(it->first->get_fd(), &sets.write_fds)) {
                        if (!process_writable(*it)) break;    
                    }

                    if (FD_ISSET(it->first->get_fd(), &sets.exception_fds)) {
                        if (!process_except(*it)) break;
                    }
                }
            }

            void selector::unregister_closed_fds(fd_sets& sets) {
                std::map<socket*, payload_type>::iterator it = elements.begin();
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

            void selector::select() {
                fd_sets  sets;

                add_fds(sets);

                timeval tv;

                tv.tv_sec = 0;
                tv.tv_usec = 50000;

                int status = ::select(sets.highest + 1, &sets.read_fds, &sets.write_fds, &sets.exception_fds, &tv);
                if (status < 0) {
                    // throw std::runtime_error("select(...) returned an error code!");
                    return;
                }

                process_fds(sets);
                unregister_closed_fds(sets);
            }

        }
    }
}
