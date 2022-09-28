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

        enum http_method {
            // http_method_options,
            http_method_get,
            // http_method_head,
            http_method_post,
            // http_method_put,
            http_method_delete,
            // http_method_trace,
            // http_method_connect
        }; // class http_method

        class http_version {
            /* TODO */
        }; // class http_version

        class request_line {
        private:
            enum http_method   _method;
                 uri           _uri;
                 http_version  _http_version;
        
        public:
            void set_method(enum http_method m) { _method = m; }
            uri& get_uri() { return _uri; }
            http_version& get_version() { return _http_version; }
            http_method&  get_method() { return _method; }

        }; // class request_line


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
            request_line& get_line()   { return _line;   }
            fields&       get_fields() { return _fields; }
        }; // class request_core

    } // namespace http
} // namespace webserv


#endif
