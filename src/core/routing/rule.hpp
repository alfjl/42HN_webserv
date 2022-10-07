#ifndef WEBSERV_CORE_ROUTING_RULE_HPP
#define WEBSERV_CORE_ROUTING_RULE_HPP

#include "../../util/path.hpp"

namespace webserv {
    namespace core {
        
        class basic_rule {
            webserv::util::path     _prefix;
            webserv::util::path     _extension;

        public:
            basic_rule();

            webserv::util::path get_prefix();
            webserv::util::path get_extension();

            void set_prefix(webserv::util::path path);
            void set_extension(webserv::util::path path);

            virtual bool matches(webserv::util::path path) = 0;
        };

        class prefix_rule : public basic_rule {
        public:
            prefix_rule(webserv::util::path prefix);

            bool matches(webserv::util::path path);
        };

        class ext_rule : public basic_rule {
        public:
            ext_rule(webserv::util::path extension);

            bool matches(webserv::util::path path);
        };

        class prefix_ext_rule : public basic_rule {
        public:
            prefix_ext_rule(webserv::util::path prefix, webserv::util::path extension);

            bool matches(webserv::util::path path);
        };

    }
}

#endif
