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
            bool                               _case_sensitive;

            bool get(std::string key, std::string& value) const;
        
        public:
            fields();
            ~fields();

            bool has(std::string key) const;

            std::string get_or_default(std::string key, std::string deflt) const;
            bool        get_int_or_default(std::string key, int& value, int default_value) const;
            int         get_int_or_default(std::string key, int default_value) const;
            
            void        put(std::string key, std::string value);
            void        put(std::string key, int value);

            void case_insensitive();

            const_iterator begin() const;
            const_iterator end() const;
        };

        std::ostream& operator<<(std::ostream& o, fields f);

    }
}

#endif
