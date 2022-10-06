#include "defs.hpp"

#include "core/instance.hpp"

void test_sockets();
void test_uri_parsing();

void test_all() {
    std::cout << "\nHello, 42 world!" << std::endl;
    std::cout << "\n --------- SOCKETS --------- \n" << std::endl;
    test_sockets();
    std::cout << "\n --------- URI PARSING --------- \n" << std::endl;
    test_uri_parsing();
}

void webserv_main() {
    webserv::core::instance  the_webserv;

    the_webserv.on_port(4242);
    the_webserv.run();
}

int main(int argc, char *argv[]) {
    //test_all();
    webserv_main();
    return 0;
}
