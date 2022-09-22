#ifndef WEBSERV_HTTP_RESPONSE_HPP
#define WEBSERV_HTTP_RESPONSE_HPP

#include "../defs.hpp"

#include "../util/connection.hpp"

// #include "uri.hpp"
#include "fields.hpp"

namespace webserv {
    namespace http {

        /*
         * This section implements an HTTP response, as described in:
         *
         *     https://www.rfc-editor.org/rfc/rfc2616#section-6
         * 
         *                                       - alanghan
         */

        class http_response {
        
        private:
            fields  _fields;
            int     _code;

        public:
        /*
         * Accepts a status code and sends the correct response back to the connection
        */
            void    write(int code, webserv::util::connection& con);

        }; // class http_response

    } // namespace http
} // namespace webserv


#endif
