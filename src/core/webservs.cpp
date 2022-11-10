#include "webservs.hpp"

namespace webserv {
    namespace core {
        webservs::webservs() : _is_running(true) {

        }

        webservs::~webservs() {
            while (!_instances.empty()) {
                delete _instances.back();
                _instances.pop_back();
            }
        }

        bool webservs::is_running() { return _is_running; }

        instance* webservs::new_instance() {
            instance* i = new instance(*this);
            _instances.push_back(i);
            return i;
        }

        bool webservs::is_busy() {
            for (std::vector<instance*>::const_iterator it = _instances.begin(); it != _instances.end(); ++it) {
                if ((*it)->is_busy())
                    return true;
            }
            return false;
        }

        void webservs::tick() {
            for (std::vector<instance*>::const_iterator it = _instances.begin(); it != _instances.end(); ++it) {
                (*it)->tick();
            }
        }

        void webservs::run() {
            if (_instances.empty())
                throw std::runtime_error("No server instances specified!");
            
            while (is_running())
                tick();
        }

        void webservs::interrupt() {
            _is_running = false;
        }
    }
}

