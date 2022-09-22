#ifndef WEBSERV_HTTP_RESPONSE_HPP
#define WEBSERV_HTTP_RESPONSE_HPP

#include "../defs.hpp"

#include "../util/connection.hpp"

#include "request.hpp" 

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
             * Default constructor initializes the members
             * with members from http_request
             */
            http_response(webserv::http::request_core& request);

            /*
             * Extracts the ostream of the connection
             * and passes it on as its return value
             */
            std::ostream& out(webserv::util::connection& con);

            /*
             * Writes the status_code and corresponding message (e.g. 200 OK)
             * of the http_response to the connection
             */
            void    write_code(webserv::util::connection& con);

            /*
             * Writes the body of the http_response to the connections ostream
             */
            virtual void    write_body(webserv::util::connection& con); // TODO: 'virtual' really needed?

            /*
             * Accepts a status code and writes the correct response back
             * to the connections ostream
             */
            void    write(int code, webserv::util::connection& con);

        }; // class http_response

    } // namespace http
} // namespace webserv


#endif
