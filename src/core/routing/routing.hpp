#ifndef WEBSERV_CORE_ROUTING_ROUTING_HPP
#define WEBSERV_CORE_ROUTING_ROUTING_HPP

#include "../component.hpp"

#include "../../http/proto/response.hpp"
#include "../../http/proto/request.hpp"
#include "../../pal/net/socket.hpp"
#include "../../pal/net/selector.hpp"
#include "../../pal/fs/fs.hpp"

#include "table/routing_table.hpp"

#include "components/component_pages.hpp"
#include "components/component_http.hpp"
#include "components/component_cgi.hpp"

namespace webserv {
    namespace http { class http_handler; }

    namespace core {

        class   selector;

        class routing : public instance_component {
            unsigned int                    _recursion_count;

            webserv::http::http_handler&    _the_http_handler;
            webserv::http::request&         _the_request;
            webserv::http::response_fixed   _the_response;

            routing_component_pages         _component_pages;
            routing_component_http          _component_http;
            routing_component_cgi           _component_cgi;
        
        public:
            routing(instance& the_inst, webserv::http::http_handler& the_http_handler, webserv::http::request& the_request);
            ~routing();

            routing_table& get_table();

            unsigned int   get_recursion_count();
            
            webserv::http::http_handler&    get_http_handler();
            webserv::http::request&         get_request();
            webserv::http::response_fixed&  get_response();

            routing_component_pages&        get_component_pages();
            routing_component_http&         get_component_http();
            routing_component_cgi&          get_component_cgi();

        protected:
            void handle_http_head(route& route);
            void handle_http_get(route& route);
            void handle_http_post(route& route);
            void handle_http_delete(route& route);

            void handle_cgi(cgi_route& route);

            void error_page(unsigned int code);

            void _follow_route(route* route);

        public:
            void follow_route(route* route);
            void look_up();
            void error_and_flush(unsigned int code);
        };

    }
}

#endif
