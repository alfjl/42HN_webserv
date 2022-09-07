#ifndef WEBSERV_HTTP_REQUEST_HPP
#define WEBSERV_HTTP_REQUEST_HPP

#include "uri.hpp"
#include "fields.hpp"

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

        enum request_method {
            // request_method_options,
            request_method_get,
            // request_method_head,
            request_method_post,
            // request_method_put,
            request_method_delete,
            // request_method_trace,
            // request_method_connect
        };

        typedef uri request_uri;

        class http_version {
            /* TODO */
        };

        class request_line {
        private:
            enum request_method _method;
                 request_uri    _uri;
                 http_version   _http_version;
        
        public:
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
        class request_core {
        private:
            request_line  _line;
            fields        _fields;
        
        public:
        };

    }
}


#endif
