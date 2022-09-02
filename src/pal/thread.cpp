#include "thread.hpp"

namespace webserv::pal {

    thread::thread() {
        created = false;
    }

    thread::~thread() {
        if (created) {
            join();
        }
    }

    void thread::start(void* (*routine)(void* arg), void* arg) {
        if (created)
            throw std::runtime_error("Thread was already created!");

        if (pthread_create(&the_thread, NULL, routine, arg) != 0) {
            throw std::runtime_error("pthread_create(...) returned an error code!");
        }

        created = true;
    }

    void* thread::join() {
        void*  retval;

        if (!created)
            throw std::runtime_error("Can not join thread (was not forked!)");
        
        if (pthread_join(the_thread, &retval) != 0) {
            throw std::runtime_error("pthread_join(...) returned an error code!");
        }

        return retval;
    }
}
