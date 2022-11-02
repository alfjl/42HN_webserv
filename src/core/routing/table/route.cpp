#include "route.hpp"

namespace webserv {
    namespace core {

        static webserv::util::path concat_path_with_info(webserv::util::path file_target, match_info& info) {
            return (file_target + info.wildcard_path);
        }


        route::route(webserv::util::path file_target) : _file_target(file_target), _meta(new route_meta()) {
            _meta->increment_refcount();
        }


        route::route(webserv::util::path file_target, route_meta* meta) : _file_target(file_target), _meta(meta) {
            _meta->increment_refcount();
        }

        route::route(const route& other) {
            if (this != &other)
                _file_target = other._file_target;
        }

        route::~route() {
            _meta->decrement_refcount();
        }

        webserv::util::path route::get_file_target() { return _file_target; }

        webserv::pal::cpp::optional<webserv::util::path> route::get_added_path() {
            return _meta->get_added_path();
        }

        bool route::is_method_allowed(webserv::http::http_method method) {
            return _meta->is_method_allowed(method);
        }

        bool route::is_directory_listing_on() {
            return _meta->is_directory_listing_on();
        }

        bool route::is_added_path_on() {
            return _meta->is_added_path_on();
        }

        webserv::pal::cpp::optional<unsigned int> route::get_max_body() {
            return _meta->get_max_body();
        }

        route* route::set_path(webserv::util::path file_target) {
            _file_target = file_target;

            return this;
        }

        route* route::disable_all_methods() {
            _meta->disable_all_methods();
            return this;
        }

        route* route::set_allowed_method(webserv::http::http_method method) {
            _meta->set_allowed_method(method);

            return this;
        }

        route* route::unset_allowed_method(webserv::http::http_method method) {
            _meta->unset_allowed_method(method);

            return this;
        }

        route* route::set_max_body(unsigned int max) {
            _meta->set_max_body(max);

            return this;
        }

        route* route::set_directory_listing(bool state) {
            _meta->set_directory_listing(state);

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

        file_route::file_route(webserv::util::path file_target, webserv::pal::cpp::optional<webserv::util::path> added_path) : route(file_target) {
            _meta->set_added_path(added_path);
            _meta->increment_refcount();
        }

        file_route::file_route(webserv::util::path file_target, route_meta* meta) : route(file_target, meta) {

        }

        file_route::file_route(const file_route& other) : route(other) {

        }
        
        route* file_route::build(match_info& info) {
            return (new file_route(webserv::util::path(concat_path_with_info(route::get_file_target(), info)), route::_meta));
        }


        cgi_route::cgi_route(webserv::util::path file_target) : route(file_target) {

        }

        cgi_route::cgi_route(webserv::util::path file_target, route_meta* meta) : route(file_target, meta) {

        }

        cgi_route::cgi_route(const cgi_route& other) : route(other) {

        }

        bool cgi_route::is_cgi() {
            return true;
        }
        
        route* cgi_route::build(match_info& info) {
            return (new cgi_route(webserv::util::path(concat_path_with_info(route::get_file_target(), info)), route::_meta));            
        }

        webserv::pal::cpp::optional<std::string> cgi_route::get_executor() {
            return _meta->get_executor();
        }

        cgi_route* cgi_route::set_executor(std::string executor) {
            _meta->set_executor(executor);
            return this;
        }


        redirection_route::redirection_route(webserv::util::path file_target) : route(file_target) {

        }

        redirection_route::redirection_route(webserv::util::path file_target, route_meta* meta) : route(file_target, meta) {

        }

        redirection_route::redirection_route(const redirection_route& other) : route(other) {

        }

        bool redirection_route::is_redirection() {
            return true;
        }
        
        route* redirection_route::build(match_info& info) {
            return (new redirection_route(webserv::util::path(concat_path_with_info(route::get_file_target(), info)), route::_meta));
        }


        permanent_redirection_route::permanent_redirection_route(webserv::util::path file_target) : route(file_target) {

        }

        permanent_redirection_route::permanent_redirection_route(webserv::util::path file_target, route_meta* meta) : route(file_target, meta) {

        }

        permanent_redirection_route::permanent_redirection_route(const permanent_redirection_route& other) : route(other) {

        }

        bool permanent_redirection_route::is_permanent_redirection() {
            return true;
        }
        
        route* permanent_redirection_route::build(match_info& info) {
            return (new permanent_redirection_route(webserv::util::path(concat_path_with_info(route::get_file_target(), info)), route::_meta));
        }

        error_route::error_route(int code) : route(webserv::util::path()), _code(code) {

        }

        error_route::error_route(int code, route_meta* meta) : route(webserv::util::path(), meta), _code(code) {

        }

        error_route::error_route(const error_route& other) : route(other), _code(other._code) {
        }

        bool error_route::is_error(int& code) {
            code = _code;
            return true;
        }
        
        route* error_route::build(match_info& info) {
            (void) info;
            return (new error_route(_code, route::_meta));
        }

        // wildcard_route::wildcard_route(webserv::util::path file_target) : route(file_target) {

        // }

        // wildcard_route::wildcard_route(const wildcard_route& other) : route(other) {

        // }

        // route* wildcard_route::build(match_info& meta) {
        //     file_route* fr = new file_route(get_file_target() + meta.wildcard_path);
        //     // if (_allowed_methods.enabled()) {
        //     if (_allowed_methods.enabled()) {
        //         std::set<webserv::http::http_method>::const_iterator it = _allowed_methods.value().begin();
        //         while (it != _allowed_methods.value().end()) {
        //             fr->set_allowed_method(*it);
        //             ++it;
        //         }
        //     }
        //     return fr;
        // }
    }
}
