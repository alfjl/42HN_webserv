#include <vector>

#include "../threading/threading.hpp"

struct test_task : public webserv::threading::task<int> {
    test_task(arg_type arg) : task(arg) {}
    void run() {
        std::cout << "Hello from task " << get() << "!" << std::endl;
    }
};

void test_threads() {
    std::vector<webserv::threading::thread<test_task>*> threads;
    for (int x = 0; x < 10; x++)
        threads.push_back(new webserv::threading::thread<test_task>(test_task(x)));
    for (std::vector<webserv::threading::thread<test_task>*>::iterator it = threads.begin();
         it != threads.end();
         ++it)
    {
        (*it)->start();
    }

    for (std::vector<webserv::threading::thread<test_task>*>::iterator it = threads.begin();
         it != threads.end();
         ++it)
    {
        delete *it;
    }

    std::cout << "Done!" << std::endl;
}
