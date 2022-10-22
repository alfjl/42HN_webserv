#include "notification.hpp"

namespace webserv {
    namespace util {

        notification::notification() {
            closed = false;
        }


        void notification::close() {
            closed = true;
        }

        bool notification::is_closed() {
            return closed;
        }


        void notification::react_close() {
            close();
        }

    }
}
