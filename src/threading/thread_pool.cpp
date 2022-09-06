#include "thread_pool.hpp"

namespace webserv {
	namespace threading {
	

	struct worker_thread_task : public task<thread_pool&> {
		worker_thread_task(arg_type arg) : task(arg) {}

	/* TODO: Propper interuption of the threads in run() */

		void run() {
			while (!get().is_terminating()) {
				basic_task* t = get().next_task();
				if (t != NULL) {
					t->run();
					delete t;
				}
			}
			std::cout << "Ending Worker_thread_task" << std::endl;
		}
	};
	
	thread_pool::thread_pool(unsigned int amount){
		for (unsigned int i = 0; i < amount; i++) {
			thread<worker_thread_task>* thr = new thread<worker_thread_task>(worker_thread_task(*this));
			_threads.push_back(thr);
			thr->start();
		}
	}
	
	thread_pool::~thread_pool() {
		for (std::vector<thread<worker_thread_task>*>::iterator i = _threads.begin(); i != _threads.end(); i++) {
			delete(*i);
		}
	}
		
	basic_task* thread_pool::next_task() {
		basic_task* t = NULL;
		{
			cond.lock();
			if (_waiting_tasks.empty()) {
				cond.wait();
			}
			if (!_waiting_tasks.empty()) {
				t = _waiting_tasks.front();
				_waiting_tasks.pop();
			}
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

	void thread_pool::interrupt() {
		cond.lock();
		_is_terminating = true;
		cond.unlock();
		for (std::vector<thread<worker_thread_task>*>::iterator i = _threads.begin(); i != _threads.end(); i++) {
			(*i)->interrupt();
		}
		cond.lock();
		cond.signal_all();
		cond.unlock();
	}

	bool thread_pool::is_terminating() {
		cond.lock();
		bool value = _is_terminating;
		cond.unlock();
		return value;
	}

	}
}