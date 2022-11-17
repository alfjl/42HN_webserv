#ifndef WEBSERV_CORE_ROUTING_COMPONENTS_COMPONENT_HPP
#define WEBSERV_CORE_ROUTING_COMPONENTS_COMPONENT_HPP

#include "../../../defs.hpp"
#include "../../../util/component.hpp"

#include "../../../http/proto/request.hpp"
#include "../../../http/proto/response.hpp"

namespace webserv {
    namespace http { class http_handler; }

    namespace core {

        class routing;
        class instance;

        class routing_component : public webserv::util::component<routing> {
        public:
            routing_component(routing& routing);
            ~routing_component();

            instance& get_instance();

            webserv::http::http_handler&    get_http_handler();
            webserv::http::request&         get_request();
            webserv::http::response_fixed&  get_response();
        };

    }
}

#endif
