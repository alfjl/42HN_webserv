#ifndef WEBSERV_CORE_ROUTING_ROUTING_HPP
#define WEBSERV_CORE_ROUTING_ROUTING_HPP

#include "../component.hpp"

#include "../../http/http_response.hpp"
#include "../../http/request.hpp"
#include "../../pal/net/socket.hpp"
#include "../../pal/net/selector.hpp"

namespace webserv {
    namespace core {

        class   selector;

        class routing : public component {

        public:
            routing(instance& the_inst);
            ~routing();

            webserv::http::http_response* look_up(webserv::http::request_core& request);

            void tick();

        }; // class selector

        class routing_table {
            // file_system  _fs;// TODO: routing_table should get an instance of the ?virtual? file system as private member
        
        public:
            routing_table(/* instance of ?virtual? file system*/) /*: _fs(fs)*/{}
            ~routing_table() {}

            webserv::http::path query(webserv::http::path oldpath);

        }; // class routing_table

    } // namespace core
} // namespace webserv

#endif
