#ifndef WEBSERV_PAL_THREAD_HPP
#define WEBSERV_PAL_THREAD_HPP

#include "../defs.hpp"

namespace webserv::pal {

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

#endif
