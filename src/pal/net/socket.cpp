#include "socket.hpp"

namespace webserv {
    namespace pal {
        namespace net {

    socket::socket() {
        fd = ::socket(PF_INET, SOCK_STREAM, 0);
    }

    socket::socket(int _fd) {
        fd = _fd;
    }

    socket::~socket() {
        close();
    }

    /*
     * Sets socket to non-blocking state, throws error if fcntl() fails
     */
    void socket::set_non_blocking() {
        int flags = fcntl(fd, F_GETFL, 0); // read out the current flags of fd, for later use when setting non-blocking
        if (flags == -1) // if fcntl went wrong, throw error
            throw std::runtime_error("fcntl(fd, F_GETFL, 0) returned an error code!");
        int status = fcntl(fd, F_SETFL, flags | O_NONBLOCK); // set fd to non-blocking
        if (status == -1) // if fcntl went wrong, throw error
            throw std::runtime_error("fcntl(fd, F_SETFL, flags | O_NONBLOCK) returned an error code!");
    // TODO add setsockopt() for portability
    }

    void socket::close() {
        if (fd >= 0)
            ::close(fd);
        fd = -1;
    }


    server_socket::~server_socket() {}

    /*
     * Accepts an incoming request
     */
    data_socket* server_socket::accept() {
        int status = ::accept(this->get_fd(), NULL, NULL);
        if (status == -1)
            throw std::runtime_error("accept(...) returned an error code!");
        return (new data_socket(status));
    }

    /*
     * 
     */
    void server_socket::listen(int number_elements_queue) {
        int status = ::listen(this->get_fd(), number_elements_queue);
        if (status == -1)
            throw std::runtime_error("listen(...) returned an error code!");
    }

    /*
     * 
     */
    void server_socket::bind(int port) {
        struct sockaddr_in server_address;
        memset(&server_address, 0, sizeof(server_address)); // TODO: Check if we are allowed to use memset()
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port);
        int status = ::bind(this->get_fd(), (struct sockaddr *)server_address, sizeof(server_address));
        if (status == -1)
            throw std::runtime_error("accept(...) returned an error code!");
    }

    data_socket::data_socket(int _fd) : socket(_fd) {}

        } // namespace net
    } // namespace pal
} // namespace webserv
