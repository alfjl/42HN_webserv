#include "route.hpp"  // for match_info. TODO: move to own file

#include "rule.hpp"

namespace webserv {
    namespace core {

        rule::rule() : _match_mode(rule_match_mode_always) {

        }

        rule::~rule() {

        }

        webserv::util::path rule::get_prefix() {
            return _path;
        }

        webserv::pal::cpp::optional<std::string>& rule::get_extension() {
            return _extension;
        }

        enum rule::match_mode rule::get_match_mode() {
            return _match_mode;
        }

        void rule::set_identity(webserv::util::path identity) {
            _match_mode = rule_match_mode_identity;
            _path       = identity;
        }

        void rule::set_prefix(webserv::util::path prefix) {
            _match_mode = rule_match_mode_prefix;
            _path       = prefix;
        }

        void rule::set_extension(std::string extension) {
            _extension.enable(extension);
        }

        void rule::set_match_mode(enum rule::match_mode mode) {
            _match_mode = mode;
        }

        bool rule::matches(webserv::util::path path, match_info& meta) {
            webserv::util::path ext(path.get_extension());

            if (get_extension().enabled() && !ext.is_equal(get_extension().value()))
                return false;

            switch (_match_mode) {
                case rule_match_mode_always: break;
                case rule_match_mode_never: return false;
                case rule_match_mode_identity:
                    if (path != get_prefix())
                        return false;
                    meta.wildcard_path = webserv::util::path();
                    break;
                case rule_match_mode_prefix:
                    if (!path.begins_with_cut(get_prefix(), meta.wildcard_path))
                        return false;
                    break;
                default: return false;
            }

            return true;
        }


        fallback_rule::fallback_rule() {
            set_match_mode(rule_match_mode_always);
        }


        identity_rule::identity_rule(webserv::util::path id_path) {
            rule::set_identity(id_path);
        }

        prefix_rule::prefix_rule(webserv::util::path prefix) {
            rule::set_prefix(prefix);
        }


        ext_rule::ext_rule(std::string extension) {
            rule::set_extension(extension);
        }


        prefix_ext_rule::prefix_ext_rule(webserv::util::path prefix, std::string extension) {
            rule::set_prefix(prefix);
            rule::set_extension(extension);
        }

    }
}
