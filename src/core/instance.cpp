#include "instance.hpp"

namespace webserv {
    namespace core {

        instance::instance() : _driver(*this) {

        }

        instance::~instance() {
            
        }

        void instance::run() {
            while (is_running()) {
                driver.tick();
            }
        }

    }
}
