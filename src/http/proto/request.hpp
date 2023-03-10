#ifndef WEBSERV_HTTP_REQUEST_HPP
#define WEBSERV_HTTP_REQUEST_HPP

#include "../../pal/net/ip_connection.hpp"
#include "../../util/binbuf.hpp"

#include "../uri.hpp"
#include "../fields.hpp"

namespace webserv {
    namespace http {

        /*
         * This section implements an HTTP request line, as described in:
         *
         *     https://www.rfc-editor.org/rfc/rfc2616#section-5.1
         * 
         * Some `request_method`s have been left out since there is no
         * immediate requirement to implement them.
         *                                       - nijakow
         */

        enum http_method {
            http_method__invalid,
            // http_method_options,
            http_method_get,
            http_method_head,
            http_method_post,
            http_method_put,
            http_method_delete,
            // http_method_trace,
            // http_method_connect
        };

        class http_version {};

        class request_line {
        private:
            enum http_method   _method;
                 uri           _uri;
                 http_version  _http_version;
        
        public:
            void set_method(enum http_method m);
            uri& get_uri();
            http_version& get_version();
            http_method&  get_method();
        };


        /*
         * This class implements an HTTP request core, as described in:
         *
         *     https://www.rfc-editor.org/rfc/rfc2616#section-5
         * 
         * More specifically, this class leaves out the message body, as it
         * may be delivered in a chunked format.
         *                                       - nijakow
         */
        class request {
            request_line                     _line;
            fields                           _fields;
            webserv::util::binary_buffer     _body;
            webserv::pal::net::ip_connection _conn;
        
        public:
            request();

            request_line&                      get_line();
            fields&                            get_fields();
            webserv::util::binary_buffer&      get_body();
            webserv::pal::net::ip_connection&  get_conn();
        };

    }
}


#endif
