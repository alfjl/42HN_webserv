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

        class instance {
            driver      _driver;
            scheduler   _scheduler;
            routing     _routing;
            filesystem  _fs;

            webserv::pal::cpp::optional<unsigned int>    _max_len;

		    bool is_interrupted;
            
            void banner();

        public:
            instance();
            ~instance();

            driver&     get_driver()    { return _driver; }
            scheduler&  get_scheduler() { return _scheduler; }
            routing&    get_routing()   { return _routing; }
            filesystem& get_fs()        { return _fs; }

		    void interrupt();
		    bool was_interrupted();
            
            void pass_connection(webserv::util::connection* new_connection);
            webserv::http::cgi_handler* pass_cgi(int cgi_fd);

            bool is_running();

            void run();

            void on_port(int port);
            void set_anchor(webserv::util::path path);
            void set_max_len(unsigned int len);
        };

    }
}

#endif
