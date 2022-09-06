#ifndef WEBSERV_THREADING_THREAD_POOL_HPP
#define WEBSERV_THREADING_THREAD_POOL_HPP

#include "../defs.hpp"
#include "mutex.hpp"
#include "task.hpp"
#include "thread.hpp"

namespace webserv {
	namespace threading {

	struct worker_thread_task;

	class thread_pool{
	public:
		thread_pool(unsigned int amount);
		~thread_pool();
		basic_task* next_task();
		void  add_task(basic_task* t);

		void interrupt();

		bool is_terminating();

		
	private:
		std::queue<basic_task*>                  _waiting_tasks;
		std::vector<thread<worker_thread_task>*> _threads;
		webserv::threading::condvar              cond;
		bool                                     _is_terminating;

	};
	
	}
}


#endif