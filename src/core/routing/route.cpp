#include "route.hpp"

namespace webserv {
    namespace core {

        route::route(webserv::util::path file_target) : _file_target(file_target) {

        }

        route::route(const route& other) {
            if (this != &other)
                _file_target = other._file_target;
        }

        route::~route() {

        }

        webserv::util::path route::get_file_target() { return _file_target; }

        bool route::is_method_allowed(webserv::http::http_method method) {
            if (!_allowed_methods.enabled())
                return true;
            return _allowed_methods.value().find(method) != _allowed_methods.value().end();
        }

        route* route::set_path(webserv::util::path file_target) {
            _file_target = file_target;

            return this;
        }

        route* route::set_allowed_method(webserv::http::http_method method) {
            _allowed_methods.enable();
            _allowed_methods.value().insert(method);

            return this;
        }

        route* route::unset_allowed_method(webserv::http::http_method method) {
            _allowed_methods.value().erase(method);

            return this;
        }


        bool route::is_cgi() {
            return false;
        }

        bool route::is_redirection() {
            return false;
        }

        bool route::is_permanent_redirection() {
            return false;
        }

        bool route::is_error(int& code) {
            code = 69420;
            return false;
        }


        file_route::file_route(webserv::util::path file_target) : route(file_target) {

        }

        file_route::file_route(const file_route& other) : route(other) {

        }


        cgi_route::cgi_route(webserv::util::path file_target) : route(file_target) {

        }

        cgi_route::cgi_route(const cgi_route& other) : route(other) {

        }

        bool cgi_route::is_cgi() {
            return true;
        }


        redirection_route::redirection_route(webserv::util::path file_target) : route(file_target) {

        }

        redirection_route::redirection_route(const redirection_route& other) : route(other) {

        }

        bool redirection_route::is_redirection() {
            return true;
        }


        permanent_redirection_route::permanent_redirection_route(webserv::util::path file_target) : route(file_target) {

        }

        permanent_redirection_route::permanent_redirection_route(const permanent_redirection_route& other) : route(other) {

        }

        bool permanent_redirection_route::is_permanent_redirection() {
            return true;
        }

        error_route::error_route(int code) : route(webserv::util::path()), _code(code) {

        }

        error_route::error_route(const error_route& other) : route(other), _code(other._code) {
        }

        bool error_route::is_error(int& code) {
            code = _code;
            return true;
        }

        wildcard_route::wildcard_route(webserv::util::path file_target) : route(file_target) {

        }

        wildcard_route::wildcard_route(const wildcard_route& other) : route(other) {

        }

        route* wildcard_route::build(route_meta& meta) {
            file_route* fr = new file_route(get_file_target() + meta.wildcard_path);
            if (_allowed_methods.enabled()) {
                std::set<webserv::http::http_method>::const_iterator it = _allowed_methods.value().begin();
                while (it != _allowed_methods.value().end()) {
                    fr->set_allowed_method(*it);
                    ++it;
                }
            }
            return fr;
        }
    }
}
