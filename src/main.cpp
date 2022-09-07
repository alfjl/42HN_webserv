#include "defs.hpp"

void test_thread_pool();
void test_shared_ptr ();
void test_guarded_borrow ();

int main(int argc, char *argv[]) {
    std::cout << "Hello, 42 world!" << std::endl;
    test_shared_ptr ();
    test_guarded_borrow ();
    // test_thread_pool();
    return 0;
}
