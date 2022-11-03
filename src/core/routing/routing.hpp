#ifndef WEBSERV_CORE_ROUTING_ROUTING_HPP
#define WEBSERV_CORE_ROUTING_ROUTING_HPP

#include "../component.hpp"

#include "../../http/proto/response.hpp"
#include "../../http/proto/request.hpp"
#include "../../pal/net/socket.hpp"
#include "../../pal/net/selector.hpp"
#include "../../pal/fs/fs.hpp"

#include "table/routing_table.hpp"

#include "components/component_http.hpp"
#include "components/component_cgi.hpp"

namespace webserv {
    namespace http { class http_handler; }

    namespace core {

        class   selector;

        class routing : public instance_component {
            webserv::http::http_handler&    _the_http_handler;
            webserv::http::request&         _the_request;
            webserv::http::response_fixed   _the_response;

            routing_component_http          _component_http;
            routing_component_cgi           _component_cgi;
        
        public:
            webserv::http::http_handler&    get_http_handler() { return _the_http_handler; }
            webserv::http::request&         get_request() { return _the_request; }
            webserv::http::response_fixed&  get_response() { return _the_response; }

            routing_component_http&         get_component_http() { return _component_http; }
            routing_component_cgi&          get_component_cgi()  { return _component_cgi;  }

        public:
            routing(instance& the_inst, webserv::http::http_handler& the_http_handler, webserv::http::request& the_request);
            ~routing();

            routing_table& get_table();

            void look_up();
            
        protected:
            void error_page(unsigned int code);
            void follow_route(route* route);

            void handle_http_head(route& route);
            void handle_http_get(route& route);
            void handle_http_post(route& route);
            void handle_http_delete(route& route);

            void handle_cgi(cgi_route* route);

            void set_response_code(webserv::util::path file_path, webserv::http::response_fixed& response);
            void get_request_body(webserv::util::path file_path, webserv::http::response_fixed& response, webserv::http::request& request);
        };

    }
}

#endif
