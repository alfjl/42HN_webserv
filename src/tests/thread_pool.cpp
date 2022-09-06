#include "../threading/threading.hpp"

struct test_task : public webserv::threading::task<int> {
	test_task(arg_type arg) : task(arg) {}
	void run() {
		std::cout << "Hi from task " << get() << std::endl;
	}
};

void test_thread_pool() {
	webserv::threading::thread_pool pool(5);

	for (int i = 0; i < 100; i++) {
		pool.add_task(new test_task(i));
	}
}

