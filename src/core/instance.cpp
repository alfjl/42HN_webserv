#include "instance.hpp"

namespace webserv {
    namespace http { class cgi_handler; }

    namespace core {

        instance::instance() : _driver(*this), _scheduler(*this), _routing(*this), _fs(*this), is_interrupted(false) {
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

        webserv::http::cgi_handler*  instance::pass_cgi(int cgi_fd) {
            webserv::util::connection* connection = _driver.add_fd(cgi_fd);
            return _scheduler.register_cgi_connection(connection);
        }

        bool instance::is_running() {
            return !was_interrupted();
        }

        void instance::run() {
            while (is_running()) {
                _routing.tick();
                _driver.tick();
                _scheduler.tick();
            }
        }

        void instance::interrupt() {
            is_interrupted = true;
        }

        bool instance::was_interrupted(){
            return is_interrupted;
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
