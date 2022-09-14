#include "defs.hpp"

void test_sockets();
void test_uri_parsing();
void test_state_machine();

int main(int argc, char *argv[]) {
    std::cout << "\nHello, 42 world!" << std::endl;
    std::cout << "\n --------- SOCKETS --------- \n" << std::endl;
    test_sockets();
    std::cout << "\n --------- URI PARSING --------- \n" << std::endl;
    test_uri_parsing();
    std::cout << "\n --------- STATE MACHINE --------- \n" << std::endl;
    test_state_machine();
    return 0;
}
