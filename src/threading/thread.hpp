#ifndef WEBSERV_THREADING_THREAD_HPP
#define WEBSERV_THREADING_THREAD_HPP

#include "../pal/pthread/thread.hpp"

namespace webserv {
    namespace threading {

    template<typename R, typename T>
    class thread {
        webserv::pal::pthread::thread  the_thread;
        R  retval;

    public:
        thread() {

        }

        ~thread() {

        }

        void start(T arg) {
            the_thread.start(arg);
        }

        R join() {
            retval = the_thread.join();
            return retval;
        }

        virtual R run(T arg) = 0;
    };

    typedef thread<void*, void*> basic_thread;

    }
}

#endif
