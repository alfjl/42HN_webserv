#include "defs.hpp"

void test_thread_pool();
void test_shared_ptr ();
void test_guarded_borrow ();
void test_sockets ();

int main(int argc, char *argv[]) {
    std::cout << "Hello, 42 world!\n" << std::endl;
    std::cout << " --------- SHARED_PTR --------- \n" << std::endl;
    test_shared_ptr ();
    std::cout << " --------- GUARDED --------- \n" << std::endl;
    test_guarded_borrow ();
    std::cout << " --------- SOCKETS --------- \n" << std::endl;
    void test_sockets ();
    // std::cout << " --------- THREAD POOL --------- \n" << std::endl;
    // test_thread_pool();
    return 0;
}
