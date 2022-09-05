#ifndef WEBSERV_PAL_PTHREAD_THREAD_HPP
#define WEBSERV_PAL_PTHREAD_THREAD_HPP

#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace pthread {

    class thread {
        pthread_t  the_thread;
        bool       created;
    
    public:
        thread();
        ~thread();

        void  start(void* (*routine)(void* arg), void* arg);
        void* join();
    };

        }
    }
}

#endif
