#include "thread.hpp"

namespace webserv {
    namespace threading {

    void* start_task(void* param) {
        ((runnable*) param)->run();
        return NULL;
    }

    }
}
