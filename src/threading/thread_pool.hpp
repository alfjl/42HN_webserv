#ifndef WEBSERV_THREADING_THREAD_POOL_HPP
#define WEBSERV_THREADING_THREAD_POOL_HPP

#include "../defs.hpp"
#include "mutex.hpp"

namespace webserv {
	namespace threading {

	struct worker_thread_task;

	class thread_pool{
	public:
		thread_pool(unsigned int amount);
		~thread_pool();
		basic_task* next_task();
		void  add_task(basic_task* t);

		
	private:
		std::queue<basic_task*>                  _waiting_tasks;
		std::vector<thread<worker_thread_task>*> _threads;
		webserv::threading::condvar              cond;

	};
	
	}
}


#endif