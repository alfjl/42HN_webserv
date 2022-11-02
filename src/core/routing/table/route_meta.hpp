#ifndef WEBSERV_CORE_ROUTING_ROUTE_ROUTE_META_HPP
#define WEBSERV_CORE_ROUTING_ROUTE_ROUTE_META_HPP

#include "../../../defs.hpp"

#include "../../../http/proto/request.hpp"
#include "../../../pal/cpp/optional.hpp"
#include "../../../util/refcounted.hpp"

namespace webserv {
    namespace core {

        class route_meta : public webserv::util::refcounted {
        protected:
            webserv::pal::cpp::optional<std::set<webserv::http::http_method> >  _allowed_methods;
            webserv::pal::cpp::optional<std::string>                            _executor;
            webserv::pal::cpp::optional<unsigned int>                           _max_body;
            webserv::pal::cpp::optional<webserv::util::path>                    _index_page;
            bool                                                                _directory_listing;

        public:
            route_meta();
            ~route_meta();

            bool is_method_allowed(webserv::http::http_method method);
            bool is_directory_listing_on();
            bool is_index_enabled();

            webserv::pal::cpp::optional<std::string>         get_executor();
            webserv::pal::cpp::optional<unsigned int>        get_max_body();
            webserv::pal::cpp::optional<webserv::util::path> get_index_page();

            route_meta* disable_all_methods();
            route_meta* set_allowed_method(webserv::http::http_method method);
            route_meta* unset_allowed_method(webserv::http::http_method method);

            void set_executor(std::string executor);
            void set_max_body(unsigned int max);
            void set_index_page(webserv::util::path index);
            void set_directory_listing(bool state);
        };

    }
}

#endif
