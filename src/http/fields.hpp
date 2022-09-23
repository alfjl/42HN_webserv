#ifndef WEBSERV_HTTP_FIELDS_HPP
#define WEBSERV_HTTP_FIELDS_HPP

#include "../defs.hpp"

namespace webserv {
    namespace http {

        class fields {
        
        public:
            typedef std::map<std::string, std::string>::const_iterator const_iterator;

        private:
            std::map<std::string, std::string> _fields;
        
        public:
            fields();
            ~fields();

            std::string get_or_default(std::string key, std::string deflt) const;
            void        put(std::string key, std::string value);
            
            const_iterator begin() const;
            const_iterator end() const;

        }; // class fields

    } // namespace http
} // namespace webserv

#endif
