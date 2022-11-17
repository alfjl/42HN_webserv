#ifndef WEBSERV_PAL_NET_SOCKET_HPP
#define WEBSERV_PAL_NET_SOCKET_HPP

#include "../../defs.hpp"
#include "../../util/refcounted.hpp"
#include "ip_connection.hpp"

namespace webserv {
    namespace core { class instance; }

    namespace pal {
        namespace net {

            class socket : public webserv::util::refcounted {
                int fd;

            private:
                socket( const socket& other);

            public:
                socket();
                socket(int _fd);
                virtual ~socket();

                void set_non_blocking();
                void set_reuseaddr();

                int get_fd() const;

                virtual bool is_server_socket() const;
                virtual bool is_data_socket() const;

                void close();
            };

            class data_socket : public socket {
                webserv::pal::net::ip_connection    _ip_connection;

                data_socket( const data_socket& other);

            public:
                data_socket(int _fd);
                data_socket(int _fd, webserv::pal::net::ip_connection connection);
                ~data_socket();

                bool is_data_socket() const;
            };

            class server_socket : public socket {
                webserv::core::instance& _associated_instance;

                server_socket(const server_socket& other);
            
            public:
                server_socket(webserv::core::instance& associated_instance);
                server_socket(int _fd, webserv::core::instance& associated_instance);
                ~server_socket();

                bool is_server_socket() const;

                webserv::core::instance& get_associated_instance();

                data_socket*    accept();
                void            listen();
                void            listen(int backlog);
                void            bind(int port);
            };

        }
    }
}

#endif
