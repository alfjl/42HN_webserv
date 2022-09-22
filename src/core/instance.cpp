#include "instance.hpp"

namespace webserv {
    namespace core {

        instance::instance() : _driver(*this), _scheduler(*this), _routing(*this) {

        }

        instance::~instance() {
            
        }

        void instance::pass_connection(webserv::util::connection* new_connection) {
            _scheduler.register_connection(new_connection);
        }

        void instance::run() {
            static int i = 0;
            while (is_running()) {
                std::cout << "Hey! " << (i++) << std::endl;
                _driver.tick();
                _scheduler.tick();
                _routing.tick();
            }
        }

    } // namespace core
} // namespace webserv
