#ifndef WEBSERV_CORE_WEBSERVS_HPP
#define WEBSERV_CORE_WEBSERVS_HPP

#include "../defs.hpp"
#include "instance.hpp"
#include "driver/driver.hpp"
#include "scheduler/scheduler.hpp"

namespace webserv {
    namespace core {

        class webservs {
            driver                  _driver;
            scheduler               _scheduler;

            std::vector<instance*>           _instances;
            std::map<std::string, instance*> _instances_by_name;

            bool                    _is_running;
        
            void tick();

        public:
            webservs();
            ~webservs();

            driver& get_driver();
            scheduler& get_scheduler();

            void pass_connection(webserv::util::connection* new_connection, instance& inst);
            webserv::http::writing_handler*  pass_writing(const webserv::util::binary_buffer& message, int cgi_fd);
            webserv::http::cgi_handler* pass_cgi(int cgi_fd);

            instance* new_instance();
            instance* get_instance_by_name(std::string name);

            bool is_running();
            bool is_busy();

            void run();

            void interrupt();
        };

    }
}

#endif
