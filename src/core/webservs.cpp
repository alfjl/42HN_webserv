#include "webservs.hpp"

namespace webserv {
    namespace core {

        webservs::webservs() : _driver(*this), _scheduler(*this), _is_running(true) {

        }

        webservs::~webservs() {
            while (!_instances.empty()) {
                delete _instances.back();
                _instances.pop_back();
            }
        }

        driver& webservs::get_driver() { return _driver; }
        scheduler& webservs::get_scheduler() { return _scheduler; }

        bool webservs::is_running() { return _is_running; }

        instance* webservs::new_instance() {
            instance* i = new instance(*this);
            _instances.push_back(i);
            return i;
        }

        bool webservs::is_busy() {
            return get_scheduler().are_tasks_pending();
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

        void webservs::pass_connection(webserv::util::connection* new_connection, instance& inst) {
            get_scheduler().register_connection(new_connection, inst);
        }

        webserv::http::cgi_handler*  webservs::pass_cgi(int cgi_fd) {
            webserv::util::connection* connection = get_driver().add_fd(cgi_fd);
            return get_scheduler().register_cgi_connection(connection);
        }

        webserv::http::writing_handler*  webservs::pass_writing(const webserv::util::binary_buffer& message, int cgi_fd) {
            webserv::util::connection* connection = get_driver().add_fd(cgi_fd);
            return get_scheduler().register_writing_connection(message, connection);
        }
    }
}
