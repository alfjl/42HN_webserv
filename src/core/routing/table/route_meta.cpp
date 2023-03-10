#include "route_meta.hpp"

namespace webserv {
    namespace core {

        route_meta::route_meta() : _directory_listing(false) {

        }

        route_meta::~route_meta() {

        }

        bool route_meta::is_method_allowed(webserv::http::http_method method) {
            if (!_allowed_methods.enabled())
                return true;
            return _allowed_methods.value().find(method) != _allowed_methods.value().end();
        }

        bool route_meta::is_directory_listing_on() {
            return _directory_listing;
        }

        bool route_meta::is_added_path_on() {
            if (_added_path.enabled())
                return true;
            return false;
        }

        webserv::pal::cpp::optional<std::string> route_meta::get_executor() {
            return _executor;
        }

        webserv::pal::cpp::optional<unsigned int> route_meta::get_max_body() {
            return _max_body;
        }

        webserv::pal::cpp::optional<webserv::util::path> route_meta::get_added_path() {
            return _added_path;
        }

        route_meta* route_meta::disable_all_methods() {
            _allowed_methods.enable();
            return this;
        }

        route_meta* route_meta::set_allowed_method(webserv::http::http_method method) {
            _allowed_methods.enable();
            _allowed_methods.value().insert(method);

            return this;
        }

        route_meta* route_meta::unset_allowed_method(webserv::http::http_method method) {
            _allowed_methods.value().erase(method);

            return this;
        }

        void route_meta::set_executor(std::string executor) {
            _executor.enable(executor);
        }

        void route_meta::set_max_body(unsigned int max) {
            _max_body.enable(max);
        }

        void route_meta::set_added_path(webserv::pal::cpp::optional<webserv::util::path> added_path) {
            if (added_path.enabled())
                _added_path.enable(added_path.value());
        }

        void route_meta::set_directory_listing(bool state) {
            _directory_listing = state;
        }

    }
}
