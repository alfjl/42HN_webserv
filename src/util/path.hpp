#ifndef WEBSERV_UTIL_PATH_HPP
#define WEBSERV_UTIL_PATH_HPP

#include "../defs.hpp"

namespace webserv {
    namespace util {

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

            std::string              get_first() const;
            std::string              get_last() const;
            path                     get_rest() const;
            // std::vector<std::string> get_addr();
            std::string              get_addr_s() const;

            bool begins_with(path prefix);
            path adapt_prefix(path old_prefix, path new_prefix);
            bool is_equal(const path& rhs) const;

        }; // class path

        bool operator==(const path& lhs, const path& rhs);

        path operator+(const path& a, const path& b);

        std::ostream& operator<<(std::ostream& stream, const path& the_path);

    } // namespace util
} // namespace webserv

#endif
