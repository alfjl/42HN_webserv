#ifndef WEBSERV_PAL_NET_SELECTOR_HPP
#define WEBSERV_PAL_NET_SELECTOR_HPP

#include "../../defs.hpp"
#include "../../util/connection.hpp"

#include "socket.hpp"
#include "reactor.hpp"

namespace webserv {
    namespace core {

        class driver;

    };


    namespace pal {
        namespace net {

            class selector {
                typedef reactor*                payload_type;

            private:
                std::map<socket*, payload_type> elements; // socket = registered/active socket
                webserv::core::driver*          the_driver;
            
            protected:
                struct fd_sets {
                    int     highest;
                    fd_set  read_fds;
                    fd_set  write_fds;
                    fd_set  exception_fds;

                    fd_sets();
                };

                void add_fds(fd_sets& sets);
                void process_fds(fd_sets& sets);
                void unregister_closed_fds(fd_sets& sets);

                void error_on_socket(webserv::pal::net::socket* sock);

                bool process_readable(std::pair<webserv::pal::net::socket*, payload_type> it);
                bool process_writable(std::pair<webserv::pal::net::socket*, payload_type> it);
                bool process_except(std::pair<webserv::pal::net::socket*, payload_type> it);

            public:
                selector();
                ~selector();

                void set_driver(webserv::core::driver* driver);

                void register_socket(socket* socket, payload_type data_set);
                void register_socket(socket* socket);
                void unregister_socket(socket* socket);

                webserv::util::connection* add_fd(int fd);

                void select(bool fast_mode);
                void select();
            };

        }
    }
}

#endif
