#include "refcounted.hpp"

namespace webserv {
    namespace util {

        refcounted::refcounted() : refcount(0) {

        }

        refcounted::~refcounted() {
            
        }

        void refcounted::increment_refcount() {
            refcount++;
        }

        void refcounted::decrement_refcount() {
            if (refcount <= 1) delete this;
            else refcount--;
        }

    }
}
