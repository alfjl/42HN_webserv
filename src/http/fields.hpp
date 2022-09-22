#ifndef WEBSERV_HTTP_FIELDS_HPP
#define WEBSERV_HTTP_FIELDS_HPP

#include "../defs.hpp"

namespace webserv {
    namespace http {

        class fields {
        private:
            std::map<std::string, std::string> _fields;
        
        public:
            fields();
            ~fields();

            std::string get_or_default(std::string key, std::string deflt) const;
            void        put(std::string key, std::string value);

        }; // class fields

    } // namespace http
} // namespace webserv

#endif
