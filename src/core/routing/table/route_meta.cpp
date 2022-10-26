#include "route_meta.hpp"

namespace webserv {
    namespace core {

        route_meta::route_meta() {

        }

        route_meta::~route_meta() {

        }

        bool route_meta::is_method_allowed(webserv::http::http_method method) {
            if (!_allowed_methods.enabled())
                return true;
            return _allowed_methods.value().find(method) != _allowed_methods.value().end();
        }

        webserv::pal::cpp::optional<std::string> route_meta::get_executor() {
            return _executor;
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

    }
}
