#ifndef WEBSERV_HTTP_URI_HPP
#define WEBSERV_HTTP_URI_HPP

#include "../defs.hpp"

namespace webserv {
    namespace http {

        class path {
        public:
            typedef std::vector<std::string>::const_iterator const_iterator;

        private:
            std::vector<std::string>   _addr;

        private:
            path(std::vector<std::string> addr);

        public:
            path();
            path(std::string addr);
            ~path();

            const_iterator begin() const;
            const_iterator end() const;
            size_t         size() const;

            void mov_up();
            void mov_cd1(std::string dir);
            void mov_cd(std::string new_addr);
        
            path cd(std::string);

            std::string              get_first();
            std::string              get_last();
            path                     get_rest(); 
            std::vector<std::string> get_addr();
            std::string              get_addr_s() const;

            bool begins_with(path prefix);
            path adapt_prefix(path old_prefix, path new_prefix);
            bool is_equal(const path& rhs) const;

        }; // class path

        bool operator==(const path& lhs, const path& rhs);

        path operator+(const path& a, const path& b);

        std::ostream& operator<<(std::ostream& stream, const path& the_path);

        class uri {
            std::string   _proto;
            std::string   _server;
            unsigned int  _port;
            path          _path;
        public:
            uri();
            ~uri();

            std::string& get_proto() { return _proto; }
            std::string& get_server() { return _server; }
            unsigned int& get_port() { return _port; }
            path& get_path() { return _path; }

            const std::string& get_proto() const { return _proto; }
            const std::string& get_server() const { return _server; }
            unsigned int get_port() const { return _port; }
            const path& get_path() const { return _path; }
        
        }; // class uri
        
        std::ostream& operator<<(std::ostream& stream, const uri& the_uri);

    } // namespace http
} // namespace webserv

#endif
