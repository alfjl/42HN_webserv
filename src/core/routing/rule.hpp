#ifndef WEBSERV_CORE_ROUTING_RULE_HPP
#define WEBSERV_CORE_ROUTING_RULE_HPP

#include "../../util/path.hpp"
#include "../../pal/cpp/optional.hpp"

namespace webserv {
    namespace core {

        struct route_meta; // Oof.
        
        class basic_rule {
            webserv::util::path                       _prefix;
            webserv::pal::cpp::optional<std::string>  _extension;

        protected:
            webserv::util::path                        get_prefix();
            webserv::pal::cpp::optional<std::string>&  get_extension();

        public:
            basic_rule();
            virtual ~basic_rule();

            void set_prefix(webserv::util::path prefix);
            void set_extension(std::string extension);

            virtual bool matches(webserv::util::path path, route_meta& meta);
        };

        class prefix_rule : public basic_rule {
        public:
            prefix_rule(webserv::util::path prefix);
        };

        class ext_rule : public basic_rule {
        public:
            ext_rule(std::string extension);
        };

        class prefix_ext_rule : public basic_rule {
        public:
            prefix_ext_rule(webserv::util::path prefix, std::string extension);
        };

    }
}

#endif
