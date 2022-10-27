#ifndef WEBSERV_HTTP_RESPONSE_HPP
#define WEBSERV_HTTP_RESPONSE_HPP

#include "../../defs.hpp"

#include "../../util/connection.hpp"
#include "../../util/refcounted.hpp"
#include "../http.hpp"

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

        class response : public webserv::util::refcounted {
            fields           _fields;
            unsigned int     _code;
        
        protected:
            enum block_mode {
                block_mode_none,
                block_mode_body,
                block_mode_all
            };

            enum block_mode  _block_mode;
            bool             _is_cgi;

        private:
            void          write_status(std::ostream& stream);
            void          write_fields(std::ostream& stream);

        public:
            response();

            void          enable_cgi_mode();
            unsigned int  get_code() const;
            void          set_code(unsigned int code);
            void          set_field(std::string name, std::string value);
            void          set_field(std::string name, int value);
            virtual void  write_body(std::ostream& stream) = 0;
            void          write(std::ostream& stream);
            
            void          block_body();
            void          block_all();
        };


        class response_fixed : public response {
            std::string      _body;

        public:
            response_fixed();

            void set_code(unsigned int code);
            void set_field(std::string name, std::string value);
            void set_field(std::string name, int value);
            void set_body(std::string body, std::string content_type);
            void set_html_body(std::string body);
            void write_body(std::ostream& stream);
            void write(std::ostream& stream);
            void write(webserv::util::connection& con);
        };
        
    }
}

#endif
