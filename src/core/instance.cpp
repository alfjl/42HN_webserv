#include "instance.hpp"

namespace webserv {
    namespace core {

        instance::instance() : _driver(*this), _scheduler(*this) {

        }

        instance::~instance() {
            
        }

        void instance::pass_connection(webserv::util::connection* Conny) {
            _scheduler.register_connection(Conny);
        }

        void instance::run() {
            while (is_running()) {
                _driver.tick();
                _scheduler.tick();
            }
        }

    } // namespace core
} // namespace webserv
