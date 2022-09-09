// wrap_shared example
#include <iostream>
#include <memory>

#include "../pal/net/socket.hpp"

struct screamer {
   screamer() { std::cout << "Creating screamer " << this << std::endl; }
  ~screamer() { std::cout << "Destroying screamer " << this << std::endl; }
};

void test_sockets () {

    // int fd1 = open("./tests/testfiles/testfile1.txt", O_RDWR);
    // std::cout << "fd1 = " << fd1 << std::endl;
    int fd2 = open("./tests/testfiles/testfile2.txt", O_RDWR);
    std::cout << "fd2 = " << fd2 << std::endl;
    // int fd3 = open("./tests/testfiles/testfile3.txt", O_RDWR);
    // std::cout << "fd3 = " << fd3 << std::endl;
    // int fd4 = open("./tests/testfiles/testfile4.txt", O_RDWR);
    // std::cout << "fd4 = " << fd4 << std::endl;
    int fd5 = open("./tests/testfiles/testfile5.txt", O_RDWR);
    std::cout << "fd5 = " << fd2 << std::endl;
    int fd6 = open("./tests/testfiles/testfile6.txt", O_RDWR);
    std::cout << "fd6 = " << fd2 << std::endl;

    try {
    webserv::pal::net::socket s1;
    std::cout << "s1.fd = " << s1.get_fd() << std::endl;
    s1.set_non_blocking();
    std::cout << "s1.fd = " << s1.get_fd() << std::endl;
    s1.close();
    }
    catch (int e) {
    std::cout << "An exception occurred. Exception Nr. " << e << '\n';
    }

    try {
    webserv::pal::net::socket s2(fd2);
    std::cout << "s2.fd = " << s2.get_fd() << std::endl;
    s2.set_non_blocking();
    std::cout << "s2.fd = " << s2.get_fd() << std::endl;
    s2.close();
    }
    catch (int e) {
    std::cout << "An exception occurred. Exception Nr. " << e << '\n';
    }

    try {
    webserv::pal::net::server_socket server_s3;
    std::cout << "server_s3.fd = " << server_s3.get_fd() << std::endl;
    server_s3.set_non_blocking();
    std::cout << "server_s3.fd = " << server_s3.get_fd() << std::endl;
    server_s3.bind(4242);
    server_s3.listen();
    server_s3.close();
    }
    catch (int e) {
    std::cout << "An exception occurred. Exception Nr. " << e << '\n';
    }

    try {
    webserv::pal::net::data_socket data_s4;
    std::cout << "data_s4.fd = " << data_s4.get_fd() << std::endl;
    data_s4.set_non_blocking();
    std::cout << "data_s4.fd = " << data_s4.get_fd() << std::endl;
    data_s4.close();
    }
    catch (int e) {
    std::cout << "An exception occurred. Exception Nr. " << e << '\n';
    }

    try {
    webserv::pal::net::server_socket server_s5(fd5);
    std::cout << "server_s5.fd = " << server_s5.get_fd() << std::endl;
    server_s5.set_non_blocking();
    std::cout << "server_s5.fd = " << server_s5.get_fd() << std::endl;
    server_s5.close();
    }
    catch (int e) {
    std::cout << "An exception occurred. Exception Nr. " << e << '\n';
    }

    try {
    webserv::pal::net::data_socket data_s6(fd6);
    std::cout << "data_s6.fd = " << data_s6.get_fd() << std::endl;
    data_s6.set_non_blocking();
    std::cout << "data_s6.fd = " << data_s6.get_fd() << std::endl;
    data_s6.close();
    }
    catch (int e) {
    std::cout << "An exception occurred. Exception Nr. " << e << '\n';
    }

}