#ifndef WEBSERV_PAL_NET_SOCKET_HPP
#define WEBSERV_PAL_NET_SOCKET_HPP

#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace net {

            class socket {
                int fd;

            private:
                socket( const socket& other);

            public:
                socket();
                socket(int _fd);
                virtual ~socket();

                void set_non_blocking();
                void set_reuseaddr();

                int get_fd() const { return fd; }

                virtual bool is_server_socket() const { return false; }
                virtual bool is_data_socket()   const { return false; }

                void close();
            };

            class data_socket : public socket {
                data_socket( const data_socket& other);

            public:
                data_socket();
                data_socket(int _fd);
                ~data_socket();

                bool is_data_socket()   const { return true; }
            };

            class server_socket : public socket {
                server_socket( const server_socket& other);
            
            public:
                server_socket();
                server_socket(int _fd);
                ~server_socket();

                bool is_server_socket() const { return true; }

                data_socket*    accept();
                void            listen();
                void            listen(int backlog);
                void            bind(int port);
            };

        }
    }
}

#endif
