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
            fields           _fields;
            unsigned int     _code;
            std::string      _body;

            void          write_status(webserv::util::connection& con);
            void          write_fields(webserv::util::connection& con);

        protected:
            virtual void  write_body(webserv::util::connection& con);

        public:
            http_response();

            std::ostream& out(webserv::util::connection& con);

            void          set_code(unsigned int code);
            void          set_field(std::string name, std::string value);
            void          set_body(std::string body);
            void          write(webserv::util::connection& con);

        }; // class http_response

    } // namespace http
} // namespace webserv


#endif
