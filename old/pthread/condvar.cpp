#include "condvar.hpp"

namespace webserv {
    namespace pal {
        namespace pthread {
    
    condvar::condvar() {
        pthread_cond_init(&the_cond_var, NULL);
    }

    condvar::~condvar() {
        pthread_cond_destroy(&the_cond_var);
    }

    void condvar::wait() {
        pthread_cond_wait(&the_cond_var, &the_mutex);
    }

    void condvar::signal() {
        pthread_cond_signal(&the_cond_var);
    }

    void condvar::signal_all() {
        pthread_cond_broadcast(&the_cond_var);
    }

        }
    }
}
