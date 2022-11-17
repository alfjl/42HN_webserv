#include "socket.hpp"
#include "ip_connection.hpp"
#include "ip_address.hpp"

#include "../fs/fs.hpp"

namespace webserv {
    namespace pal {
        namespace net {

            /*
             * Constructs a new stream socket
             */
            socket::socket() {
                fd = ::socket(PF_INET, SOCK_STREAM, 0);
            }

            /*
             * Constructs a socket around an existing file descriptor
             */
            socket::socket(int _fd) {
                fd = _fd;
            }

            /*
             * Destructs a socket and calls socket::close()
             * in order to prevent a double close of an already closed socket
             */
            socket::~socket() {
                close();
            }

            /*
             * Sets socket to non-blocking state
             * Throws an exception if fcntl() encounters an error
             */
            void socket::set_non_blocking() {
                int status = fcntl(fd, F_SETFL, O_NONBLOCK);
                if (status == -1)
                    throw std::runtime_error("fcntl(fd, F_SETFL, O_NONBLOCK) returned an error code!");
            }

            /*
             * Enables REUSEADDR mode for the socket
             */
            void socket::set_reuseaddr() {
                int value = 1;

                if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int)) != 0)
                    throw std::runtime_error("setsockopt(fd, SOL_SOKET, SO_REUSEADDR, ...) returned an error code!");
            }

            /*
             * Returns fd
             */
            int socket::get_fd() const { return fd; }

            /*
             * Returns false, since it's no server socket
             */
            bool socket::is_server_socket() const { return false; }

            /*
             * Returns false, since it's no data socket
             */
            bool socket::is_data_socket()   const { return false; }

            /*
             * Closes the socket, if it is still active
             * Prevents potential problems, if program tries to close
             * a previously closed socket
             */
            void socket::close() {
                if (fd >= 0)
                    webserv::pal::fs::close(fd);
                fd = -1;
            }


            /*
             * Constructs a data_socket around an existing file descriptor
             */
            data_socket::data_socket(int _fd) : socket(_fd), _ip_connection() {}

            /*
             * Constructs a data_socket around an existing file descriptor and ip_connection
             */
            data_socket::data_socket(int _fd, webserv::pal::net::ip_connection connection) : socket(_fd), _ip_connection(connection) {}

            /*
             * Destructs a data_socket
             * Not much to be done, since 'fd' will be closed in parent instance 'socket'
             */
            data_socket::~data_socket() {}

            /*
             * Returns true, since it is a data_socket
             */
            bool data_socket::is_data_socket() const { return true; }


            /*
             * Constructs a new server_socket
             */
            server_socket::server_socket(webserv::core::instance& associated_instance) : _associated_instance(associated_instance) {}
            
            /*
             * Constructs a server_socket around an existing file descriptor
             */
            server_socket::server_socket(int _fd, webserv::core::instance& associated_instance) : socket(_fd), _associated_instance(associated_instance) {}

            /*
             * Destructs a server_socket
             * Not much to be done, since 'fd' will be closed in parent instance 'socket'
             */
            server_socket::~server_socket() {}

            webserv::core::instance& server_socket::get_associated_instance() { return _associated_instance; }

            /*
             * Returns true, since it is a server socket
             */
            bool server_socket::is_server_socket() const { return true; }

            /*
             * Accepts an incoming request
             * Throws an exception if ::accept() encounters an error
             */
            data_socket* server_socket::accept() {
                struct sockaddr_in client_addr;
                socklen_t          addr_size;

                addr_size = sizeof(struct sockaddr_in);
                int status = ::accept(this->get_fd(), (struct sockaddr*) &client_addr, &addr_size);
                if (status == -1)
                    throw std::runtime_error("accept(...) returned an error code!");
                ip_address client_ip(ntohl(client_addr.sin_addr.s_addr));
                ip_connection client_connection(client_ip, ntohs(client_addr.sin_port));

                return (new data_socket(status, client_connection));
            }

            /*
             * Sets the server_socket into listening mode
             * for 128 elements in our queue (default)
             */
            void server_socket::listen() {
                listen(128);
            }

            /*
             * Sets the server_socket into listening mode
             * for the maximum number of elements in our queue
             * Throws an exception if ::listen() encounters an error
             */
            void server_socket::listen(int backlog) {
                int status = ::listen(this->get_fd(), backlog);
                if (status == -1)
                    throw std::runtime_error("listen(...) returned an error code!");
            }

            /*
             * Tells server_socket which port it belongs to 
             * Throws an exception if ::bind() encounters an error
             */
            void server_socket::bind(int port) {

                struct sockaddr_in server_address;

                memset(&server_address, 0, sizeof(server_address));
                server_address.sin_family = AF_INET;
                server_address.sin_port = htons(port);

                int status = ::bind(this->get_fd(), 
                                    (struct sockaddr *)&server_address, 
                                    sizeof(server_address));

                if (status == -1)
                    throw std::runtime_error("bind(...) returned an error code!");
            }

        }
    }
}
