#include "rule.hpp"

namespace webserv {
    namespace core {

        basic_rule::basic_rule() : _prefix(""), _extension("") {

        }


        webserv::util::path basic_rule::get_prefix() {
            return _prefix;
        }

        webserv::util::path basic_rule::get_extension() {
            return _extension;
        }

        void basic_rule::set_prefix(webserv::util::path path) {
            _prefix = path;
        }

        void basic_rule::set_extension(webserv::util::path path) {
            _extension = path;
        }


        prefix_rule::prefix_rule(webserv::util::path prefix) {
            basic_rule::set_prefix(prefix);
        }

        bool prefix_rule::matches(webserv::util::path path) {
            return (path.begins_with(basic_rule::get_prefix())); // Does 'path' always start exactly with prefix, or might the prefix be somewhere in the middle of 'path'?
        }


        ext_rule::ext_rule(webserv::util::path extension) {
            basic_rule::set_extension(extension);
        }

        bool ext_rule::matches(webserv::util::path path) {
            webserv::util::path ext(path.get_extension());

            return ( ext.is_equal(basic_rule::get_extension()));
        }


        prefix_ext_rule::prefix_ext_rule(webserv::util::path prefix, webserv::util::path extension) {
            basic_rule::set_prefix(prefix);
            basic_rule::set_extension(extension);
        }

        bool prefix_ext_rule::matches(webserv::util::path path) {
            webserv::util::path ext(path.get_extension());

            return (path.begins_with(basic_rule::get_prefix()) && ext.is_equal(basic_rule::get_extension()));
        }

    }
}
