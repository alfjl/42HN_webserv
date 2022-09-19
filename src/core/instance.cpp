#include "instance.hpp"

namespace webserv {
    namespace core {

        instance::instance() : _driver(*this), _scheduler(*this) {

        }

        instance::~instance() {
            
        }

        void instance::pass_connection(webserv::util::connection* new_connection) {
            _scheduler.register_connection(new_connection);
        }

        void instance::run() {
            while (is_running()) {
                _driver.tick();
                _scheduler.tick();
            }
        }

    } // namespace core
} // namespace webserv
