#ifndef WEBSERV_CORE_ROUTING_ROUTE_RULE_HPP
#define WEBSERV_CORE_ROUTING_ROUTE_RULE_HPP

#include "../../../util/path.hpp"
#include "../../../pal/cpp/optional.hpp"

namespace webserv {
    namespace core {

        struct match_info;
        
        class basic_rule {
        public:
            enum match_mode {
                rule_match_mode_never,
                rule_match_mode_always,
                rule_match_mode_identity,
                rule_match_mode_prefix
            };

        private:
            enum match_mode                           _match_mode;
            webserv::util::path                       _path;
            webserv::pal::cpp::optional<std::string>  _extension;

        public:
            basic_rule();
            virtual ~basic_rule();

            enum match_mode                            get_match_mode();
            webserv::util::path                        get_prefix();
            webserv::pal::cpp::optional<std::string>&  get_extension();

            void set_identity(webserv::util::path identity);
            void set_prefix(webserv::util::path prefix);
            void set_extension(std::string extension);
            void set_match_mode(enum match_mode mode);

            virtual bool matches(webserv::util::path path, match_info& meta);
        };

        class fallback_rule : public basic_rule {
        public:
            fallback_rule();
        };

        class identity_rule : public basic_rule {
        public:
            identity_rule(webserv::util::path id_path);
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
