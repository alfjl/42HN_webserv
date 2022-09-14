#include "defs.hpp"

void test_sockets();
void test_uri_parsing();
void test_streamflow();

int main(int argc, char *argv[]) {
    std::cout << "\nHello, 42 world!" << std::endl;
    std::cout << "\n --------- SOCKETS --------- \n" << std::endl;
    test_sockets();
    std::cout << "\n --------- URI PARSING --------- \n" << std::endl;
    test_uri_parsing();
    std::cout << "\n --------- STREAMFLOW --------- \n" << std::endl;
    test_streamflow();
    return 0;
}
