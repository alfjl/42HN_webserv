#ifndef WEBSERV_CORE_ROUTING_ROUTING_HPP
#define WEBSERV_CORE_ROUTING_ROUTING_HPP

#include "../component.hpp"

#include "../../pal/net/socket.hpp"
#include "../../pal/net/selector.hpp"

namespace webserv {
    namespace core {

        class   selector;

        class routing : public component {

        public:
            routing();
            ~routing();

            webserv::pal::cpp::shared_ptr<http_response> look_up(http_request& request);

        }; // class selector

    } // namespace core
} // namespace webserv

#endif
