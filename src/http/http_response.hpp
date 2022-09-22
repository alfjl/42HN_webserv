#ifndef WEBSERV_HTTP_RESPONSE_HPP
#define WEBSERV_HTTP_RESPONSE_HPP

#include "../defs.hpp"

#include "../util/connection.hpp"

#include "request.hpp" 

namespace webserv {
    namespace http {

        /*
         * This section implements a HTTP response, as described in:
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
            http_response(webserv::http::request_core& request);

            std::ostream& out(webserv::util::connection& con);

            void          write_status(webserv::util::connection& con);
            void          write_fields(webserv::util::connection& con);
            virtual void  write_body(webserv::util::connection& con); // TODO: 'virtual' really needed?
            void          write(int code, webserv::util::connection& con);

        }; // class http_response

    } // namespace http
} // namespace webserv


#endif
