#ifndef WEBSERV_PAL_SOCKET_SOCKET_HPP
#define WEBSERV_PAL_SOCKET_SOCKET_HPP

#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace net {

    class socket {

    private:
        int fd;

    private:
        socket( const socket& other);

    public:
        socket();
        socket(int _fd);
        virtual ~socket();

        void set_non_blocking();

        int get_fd() const { return fd; }

        virtual bool is_server_socket() const { return false; }
        virtual bool is_data_socket()   const { return false; }

        void close();

        friend class selector;
        /* TODO: Reading, writing, yada yada yada ... */

    }; // class socket


    class server_socket : public socket {
    
    private:
        server_socket( const server_socket& other);
    
    public:
        server_socket();
        ~server_socket();

        bool is_server_socket() const { return true; }
        bool is_data_socket()   const { return false; }

        void close();

        data_socket*    accept();
        void            listen(int number_elements_queue); // TODO
        void            bind(int port); // TODO

        /* TODO: Reading, writing, yada yada yada ... */

    }; // class server_socket


    class data_socket : public socket {

    private:
        data_socket( const data_socket& other);

    public:
        data_socket();
        data_socket(int _fd);
        ~data_socket();

        bool is_server_socket() const { return false; }
        bool is_data_socket()   const { return true; }

        void close();

        /* TODO: Reading, writing, yada yada yada ... */

    }; // class data_socket

        } // namespace net
    } // namespace pal
} // namespace webserv

#endif
