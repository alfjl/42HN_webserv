#include "defs.hpp"

void test_sockets();
void test_uri_parsing();

int main(int argc, char *argv[]) {
    std::cout << "\nHello, 42 world!" << std::endl;
    std::cout << "\n --------- SOCKETS --------- \n" << std::endl;
    test_sockets();
    test_uri_parsing();
    return 0;
}
