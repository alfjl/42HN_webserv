#ifndef WEBSERV_PAL_PTHREAD_CONDVAR_HPP
#define WEBSERV_PAL_PTHREAD_CONDVAR_HPP

#include "../../defs.hpp"
#include "mutex.hpp"

namespace webserv {
    namespace pal {
        namespace pthread {

    class condvar : public mutex {
        pthread_cond_t   the_cond_var;
    
    public:
        condvar();
        ~condvar();

        void wait();
        void signal();
    };

        }
    }
}

#endif
