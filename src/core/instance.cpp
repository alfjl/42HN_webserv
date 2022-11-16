#include "instance.hpp"

namespace webserv {
    namespace http { class cgi_handler; }

    namespace core {

        instance::instance(webservs& webservs) : _webservs(webservs), _driver(*this), _scheduler(*this), _fs(*this), _max_len() {
            
        }

        instance::~instance() {
            
        }

        webservs&   instance::get_webservs()  { return _webservs; }
        driver&     instance::get_driver()    { return _driver; }
        scheduler&  instance::get_scheduler() { return _scheduler; }
        filesystem& instance::get_fs()        { return _fs; }

        bool instance::get_max_len_enabled() {
            return _max_len.enabled();
        }

        webserv::pal::cpp::optional<unsigned int>& instance::get_max_len() {
            return _max_len;
        }

        routing_table& instance::get_routing_table() { return _routing_table; }

        void instance::pass_connection(webserv::util::connection* new_connection) {
            _scheduler.register_connection(new_connection, *this);
        }

        webserv::http::cgi_handler*  instance::pass_cgi(int cgi_fd) {
            webserv::util::connection* connection = _driver.add_fd(cgi_fd);
            return _scheduler.register_cgi_connection(connection);
        }

        webserv::http::writing_handler*  instance::pass_writing(const webserv::util::binary_buffer& message, int cgi_fd) {
            webserv::util::connection* connection = _driver.add_fd(cgi_fd);
            return _scheduler.register_writing_connection(message, connection);
        }

        bool instance::is_busy() {
            return get_scheduler().are_tasks_pending();
        }

        void instance::tick() {
            get_driver().tick();
            get_scheduler().tick();
        }

        void instance::on_port(int port) {
            std::cout << "Now serving on http://localhost:" << port << "/ ..." << std::endl;
            get_driver().open_port(port);
        }

        void instance::set_anchor(webserv::util::path path) {
            get_fs().set_anchor(path);
        }

        void instance::set_names(std::string name) {
            _names.push_back(name);
        }

        void instance::set_max_len(unsigned int len) {
            _max_len.enable(len);
        }

        void instance::print_server_names(){
            std::cout << "Server names: ";
            for (std::vector<std::string>::const_iterator it = _names.begin(); it != _names.end(); ++it)
                std::cout << *it << " ";
            std::cout << std::endl;
        }

    }
}
