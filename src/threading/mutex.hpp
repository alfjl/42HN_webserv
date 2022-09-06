#ifndef WEBSERV_THREADING_MUTEX_HPP
#define WEBSERV_THREADING_MUTEX_HPP

#include "../pal/pthread/mutex.hpp"

namespace webserv {
    namespace threading {

    typedef webserv::pal::pthread::mutex mutex;

    }
}

#endif
