#include "socket.hpp"

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
                int flags = fcntl(fd, F_GETFL, 0); // read out the current flags of fd, for later use when setting non-blocking
                if (flags == -1) // if fcntl went wrong, throw error
                    throw std::runtime_error("fcntl(fd, F_GETFL, 0) returned an error code!");
                int status = fcntl(fd, F_SETFL, flags | O_NONBLOCK); // set fd to non-blocking
                if (status == -1) // if fcntl went wrong, throw error
                    throw std::runtime_error("fcntl(fd, F_SETFL, flags | O_NONBLOCK) returned an error code!");
                // TODO: add setsockopt() for portability
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
             * Closes the socket, if it is still active
             * Prevents potential problems, if program tries to close
             * a previously closed socket
             */
            void socket::close() {
                if (fd >= 0)
                    ::close(fd);
                fd = -1;
            }


            /*
             * Constructs a new data_socket
             */
            data_socket::data_socket() {}

            /*
             * Constructs a data_socket around an existing file descriptor
             */
            data_socket::data_socket(int _fd) : socket(_fd) {}

            /*
             * Destructs a data_socket
             * Not much to be done, since 'fd' will be closed in parent instance 'socket'
             */
            data_socket::~data_socket() {}


            /*
             * Constructs a new server_socket
             */
            server_socket::server_socket() {}
            
            /*
             * Constructs a server_socket around an existing file descriptor
             */
            server_socket::server_socket(int _fd) : socket(_fd) {}

            /*
             * Destructs a server_socket
             * Not much to be done, since 'fd' will be closed in parent instance 'socket'
             */
            server_socket::~server_socket() {}

            /*
             * Accepts an incoming request
             * Throws an exception if ::accept() encounters an error
             */
            data_socket* server_socket::accept() {
                int status = ::accept(this->get_fd(), NULL, NULL);
                if (status == -1)
                    throw std::runtime_error("accept(...) returned an error code!");
                return (new data_socket(status));
            }

            /*
             * Sets the server_socket into listening mode
             * for 16 elements in our queue (default)
             */
            void server_socket::listen() {
                listen(16);
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

                struct sockaddr_in server_address; // generate new sockaddr struct

                memset(&server_address, 0, sizeof(server_address)); // initialize with default '0'
                server_address.sin_family = AF_INET; // set address family to IPv4 addresses
                server_address.sin_port = htons(port); // set 'port' in address struct

                int status = ::bind(this->get_fd(), 
                                    (struct sockaddr *)&server_address, 
                                    sizeof(server_address)); // bind the server_socket to 'port'

                if (status == -1)
                    throw std::runtime_error("bind(...) returned an error code!");
            }

        }
    }
}
