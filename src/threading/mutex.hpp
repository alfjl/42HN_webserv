#ifndef WEBSERV_THREADING_MUTEX_HPP
#define WEBSERV_THREADING_MUTEX_HPP

#include "../pal/pthread/mutex.hpp"
#include "../pal/pthread/condvar.hpp"

namespace webserv {
    namespace threading {

    typedef webserv::pal::pthread::mutex   mutex;
    typedef webserv::pal::pthread::condvar condvar;

    }
}

#endif
