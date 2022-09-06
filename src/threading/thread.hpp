#ifndef WEBSERV_THREADING_THREAD_HPP
#define WEBSERV_THREADING_THREAD_HPP

#include "../pal/pthread/thread.hpp"
#include "task.hpp"

namespace webserv {
    namespace threading {

    static void* start_task(void* param) {
        ((runnable*) param)->run();
        return NULL;
    }

    template<typename T>
    class thread {
        webserv::pal::pthread::thread  the_thread;
        T                              task;

    public:
        thread(T _task) : task(_task) {}

        ~thread() {}

        void start() {
            the_thread.start(start_task, &task);
        }

        void interrupt() {
            /* TODO */
        }
    };

    }
}

#endif
