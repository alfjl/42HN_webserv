#include "thread_pool.hpp"

namespace webserv {
	namespace threading {
	

	struct worker_thread_task : public task<thread_pool&> {
		worker_thread_task(arg_type arg) : task(arg) {}
		
		void run() {
			task* t = get().next_task();
			while (t != NULL) {
				t->run();
				delete t;
				task* t = get().next_task();
			}
			std::cout << "Ending Worker_thread_task" << std::endl;
		}
	};
	
	thread_pool::thread_pool(unsigned int amount){
		for (unsigned int i = 0; i < amount; i++) {
			thread<worker_thread_task>* thr = new thread<worker_thread_task>(worker_thread_task(*this));
			_threads.push_back(thr);
			thr.start();
		}
	}
	
	thread_pool::~thread_pool() {
		std::vector<thread<worker_thread_task>*>::iterator i = _threads.begin();
		while (i != _threads.end()) {
			delete(*it);
			i++;
		}
	}
		
	basic_task* thread_pool::next_task() {
		basic_task* t = NULL;
		{
			cond.lock();
			if (_waiting_tasks.empty()) {
				cond.wait();
			}
			if (!_waiting_tasks.empty())
				t = _waiting_tasks.pop();
			cond.unlock();
		}
		return t;
	}
	
	void  thread_pool::add_task(basic_task* t) {
		cond.lock();
		_waiting_tasks.push(t);
		cond.signal();
		cond.unlock();
	}

	}
}