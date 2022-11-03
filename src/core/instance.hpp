#ifndef WEBSERV_CORE_INSTANCE_HPP
#define WEBSERV_CORE_INSTANCE_HPP

#include "../defs.hpp"
#include "../util/connection.hpp"

#include "driver/driver.hpp"
#include "scheduler/scheduler.hpp"
#include "routing/routing.hpp"
#include "filesystem/filesystem.hpp"


namespace webserv {
    namespace core {

        class driver;
        class scheduler;
        class routing;

        class routing_table;

        class instance {
            driver         _driver;
            scheduler      _scheduler;
            routing        _routing;
            filesystem     _fs;
            routing_table  _routing_table;

            std::vector<std::string>  _names;

            webserv::pal::cpp::optional<unsigned int>    _max_len;

        public:
            instance();
            ~instance();

            driver&     get_driver()    { return _driver; }
            scheduler&  get_scheduler() { return _scheduler; }
            routing&    get_routing()   { return _routing; }
            filesystem& get_fs()        { return _fs; }
            
            bool get_max_len_enabled();
            webserv::pal::cpp::optional<unsigned int>& get_max_len();

            routing_table& get_routing_table() { return _routing_table; }
            
            void pass_connection(webserv::util::connection* new_connection);
            webserv::http::cgi_handler* pass_cgi(int cgi_fd);

            void tick();

            void on_port(int port);
            void set_anchor(webserv::util::path path);
            void set_names(std::string name);
            void set_max_len(unsigned int len);

            void print_server_names();
        };

    }
}

#endif
