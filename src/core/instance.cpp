#include "instance.hpp"

namespace webserv {
    namespace core {

        instance::instance() : _driver(*this), _scheduler(*this), _routing(*this), _fs(*this) {
            banner();
        }

        instance::~instance() {
            
        }

        void instance::banner() {
            std::cout << std::endl;
            std::cout << "          T h e   W e b s e r v" << std::endl;
            std::cout << std::endl;
            std::cout << "    by alanghan@student.42heilbronn.de" << std::endl;
            std::cout << "       enijakow@student.42heilbronn.de" << std::endl;
            std::cout << "        nlenoch@student.42heilbronn.de" << std::endl;
            std::cout << std::endl;
        }

        void instance::pass_connection(webserv::util::connection* new_connection) {
            _scheduler.register_connection(new_connection, _routing);
        }

        void instance::run() {
            while (is_running()) {
                _routing.tick();
                _driver.tick();
                _scheduler.tick();
            }
        }

        void instance::on_port(int port) {
            std::cout << "Now serving on http://localhost:" << port << "/ ..." << std::endl;
            get_driver().open_port(port);
        }

        void instance::set_anchor(webserv::util::path path) {
            get_fs().set_anchor(path);
        }

    }
}
