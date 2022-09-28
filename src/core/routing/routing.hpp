#ifndef WEBSERV_CORE_ROUTING_ROUTING_HPP
#define WEBSERV_CORE_ROUTING_ROUTING_HPP

#include "../component.hpp"

#include "../../http/response.hpp"
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

            webserv::http::response* look_up(webserv::http::request_core& request);

            void tick();

        }; // class routing

    } // namespace core
} // namespace webserv

#endif
