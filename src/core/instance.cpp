#include "instance.hpp"

namespace webserv {
    namespace core {

        instance::instance() : _driver(*this), _scheduler(*this) {

        }

        instance::~instance() {
            
        }

        void instance::run() {
            while (is_running()) {
                _driver.tick();
                _scheduler.tick();
            }
        }

    }
}
