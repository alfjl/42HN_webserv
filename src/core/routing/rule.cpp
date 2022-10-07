#include "rule.hpp"

namespace webserv {
    namespace core {

        basic_rule::basic_rule() {

        }

        basic_rule::~basic_rule() {

        }

        webserv::util::path basic_rule::get_prefix() {
            return _prefix;
        }

        webserv::util::optional<std::string>& basic_rule::get_extension() {
            return _extension;
        }

        void basic_rule::set_prefix(webserv::util::path prefix) {
            _prefix = prefix;
        }

        void basic_rule::set_extension(std::string extension) {
            _extension.enable(extension);
        }

        bool basic_rule::matches(webserv::util::path path) {
            webserv::util::path ext(path.get_extension());

            if (!path.begins_with(get_prefix()))
                return false;
            if (get_extension().enabled() && !ext.is_equal(get_extension().value()))
                return false;
            return true;
        }


        prefix_rule::prefix_rule(webserv::util::path prefix) {
            basic_rule::set_prefix(prefix);
        }


        ext_rule::ext_rule(std::string extension) {
            basic_rule::set_extension(extension);
        }


        prefix_ext_rule::prefix_ext_rule(webserv::util::path prefix, std::string extension) {
            basic_rule::set_prefix(prefix);
            basic_rule::set_extension(extension);
        }

    }
}
