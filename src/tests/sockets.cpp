// wrap_shared example
#include <iostream>
#include <memory>

#include "../pal/net/socket.hpp"

struct screamer {
   screamer() { std::cout << "Creating screamer " << this << std::endl; }
  ~screamer() { std::cout << "Destroying screamer " << this << std::endl; }
};

void test_sockets () {

 //TODO: test with different threads

int fd10(10);
int fd50(50);
int fd60(60);

webserv::pal::net::socket s1;
webserv::pal::net::socket s2(fd10);
webserv::pal::net::server_socket server_s3;
webserv::pal::net::data_socket data_s4;
webserv::pal::net::server_socket server_s5(fd50);
webserv::pal::net::data_socket data_s6(fd60);

std::cout << "s1.fd = " << s1.get_fd() << std::endl;
std::cout << "s2.fd = " << s2.get_fd() << std::endl;
std::cout << "server_s3.fd = " << server_s3.get_fd() << std::endl;
std::cout << "data_s4.fd = " << data_s4.get_fd() << std::endl;
std::cout << "server_s5.fd = " << server_s5.get_fd() << std::endl;
std::cout << "data_s6.fd = " << data_s6.get_fd() << std::endl;
std::cout << std::endl;

s1.set_non_blocking();
s2.set_non_blocking();
server_s3.set_non_blocking();
data_s4.set_non_blocking();

std::cout << "s1.fd = " << s1.get_fd() << std::endl;
std::cout << "s2.fd = " << s2.get_fd() << std::endl;
std::cout << "server_s3.fd = " << server_s3.get_fd() << std::endl;
std::cout << "data_s4.fd = " << data_s4.get_fd() << std::endl;
std::cout << "server_s5.fd = " << server_s5.get_fd() << std::endl;
std::cout << "data_s6.fd = " << data_s6.get_fd() << std::endl;
std::cout << std::endl;

s1.close();
s2.close();
server_s3.close();
data_s4.close();
server_s5.close();
data_s6.close();

}