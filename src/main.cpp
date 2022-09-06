#include "defs.hpp"

void test_thread_pool();
void test_shared_ptr ();

int main(int argc, char *argv[]) {
    std::cout << "Hello, 42 world!" << std::endl;
    test_shared_ptr ();
    test_thread_pool();
    return 0;
}
