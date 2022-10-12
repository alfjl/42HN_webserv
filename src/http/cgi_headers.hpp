#ifndef WEBSERV_HTTP_CGI_HEADERS_HPP
#define WEBSERV_HTTP_CGI_HEADERS_HPP

#include "../defs.hpp"

namespace webserv {
    namespace http {

        class cgi_headers {
        public:
            typedef std::map<std::string, std::string>::const_iterator const_iterator;

        private:
            std::map<std::string, std::string> _headers;
        
        public:
            cgi_headers();
            ~cgi_headers();

            bool has(std::string key) const;

            std::string get_or_default(std::string key, std::string deflt) const;
            void        put(std::string key, std::string value);
            
            const_iterator begin() const;
            const_iterator end() const;
        };

        std::ostream& operator<<(std::ostream& stream, const cgi_headers& the_headers);

    }
}

#endif
