#ifndef WEBSERV_CORE_ROUTING_RULE_HPP
#define WEBSERV_CORE_ROUTING_RULE_HPP

#include "../../util/path.hpp"
#include "../../util/optional.hpp"

namespace webserv {
    namespace core {
        
        class basic_rule {
            webserv::util::path                   _prefix;
            webserv::util::optional<std::string>  _extension;

        protected:
            webserv::util::path                    get_prefix();
            webserv::util::optional<std::string>&  get_extension();

        public:
            basic_rule();

            void set_prefix(webserv::util::path prefix);
            void set_extension(std::string extension);

            virtual bool matches(webserv::util::path path);
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
