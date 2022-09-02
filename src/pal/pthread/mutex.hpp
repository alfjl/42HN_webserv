#ifndef WEBSERV_PAL_PTHREAD_MUTEX_HPP
#define WEBSERV_PAL_PTHREAD_MUTEX_HPP

#include "../../defs.hpp"

namespace webserv::pal::pthread {

    class mutex {
        pthread_mutex_t  the_mutex;
    
    public:
        mutex();
        ~mutex();

        void lock();
        void unlock();
        bool trylock();
    };

}

#endif
