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

        class response {
            fields           _fields;
            unsigned int     _code;
        
        protected:
            bool             _blocked;

        private:
            void          write_status(webserv::util::connection& con);
            void          write_fields(webserv::util::connection& con);

        public:
            response();

            std::ostream& out(webserv::util::connection& con);

            void          set_code(unsigned int code);
            void          set_field(std::string name, std::string value);
            virtual void  write_body(webserv::util::connection& con) = 0;
            void          write(webserv::util::connection& con);
            void          block_body();
        };


        class response_fixed : public response {
            std::string      _body;

        public:
            response_fixed();

            std::ostream& out(webserv::util::connection& con);

            void set_code(unsigned int code);
            void set_field(std::string name, std::string value);
            void set_body(std::string body, std::string content_type);
            void set_html_body(std::string body);
            void write_body(webserv::util::connection& con);
            void write(webserv::util::connection& con);
        };

    }
}

#endif
