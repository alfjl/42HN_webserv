#include "mutex.hpp"

namespace webserv::pal::pthread {

    mutex::mutex() {
        /* TODO: Ensure that the mutex was created successfully */
        pthread_mutex_init(&the_mutex, NULL);
    }

    mutex::~mutex() {
        /* TODO: Ensure that the mutex was destroyed successfully */
        pthread_mutex_destroy(&the_mutex);
    }

    void mutex::lock() {
        /* TODO: Ensure that the mutex was locked successfully */
        pthread_mutex_lock(&the_mutex);
    }

    void mutex::unlock() {
        /* TODO: Ensure that the mutex was unlocked successfully */
        pthread_mutex_unlock(&the_mutex);
    }

    bool mutex::trylock() {
        if (pthread_mutex_trylock(&the_mutex) == 0)
            return true;
        /* TODO: Maybe check errno for EAGAIN, EBUSY or EINVAL */
        return (false);
    }

}
