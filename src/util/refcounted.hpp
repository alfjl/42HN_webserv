#ifndef WEBSERV_UTIL_REFCOUNTED_HPP
#define WEBSERV_UTIL_REFCOUNTED_HPP

namespace webserv {
    namespace util {

        class refcounted {
            unsigned int refcount;

        public:
            refcounted();
            virtual ~refcounted();

            void increment_refcount();
            void decrement_refcount();
        };

    }
}

#endif
