#include "defs.hpp"

#include "core/instance.hpp"

void test_thread_pool();
void test_shared_ptr ();
void test_guarded_borrow ();
void test_sockets ();

int main(int argc, char *argv[]) {
    std::cout << "\nHello, 42 world!" << std::endl;
    std::cout << "\n --------- SHARED_PTR --------- \n" << std::endl;
    test_shared_ptr ();
    std::cout << "\n --------- GUARDED --------- \n" << std::endl;
    test_guarded_borrow ();
    std::cout << "\n --------- SOCKETS --------- \n" << std::endl;
    test_sockets ();
    // std::cout << "\n --------- THREAD POOL --------- \n" << std::endl;
    // test_thread_pool();

    {
        webserv::core::instance inst;

        inst.get_driver().open_port(4242);
        inst.run();
    }

    return 0;
}
