#ifndef WEBSERV_CORE_ROUTING_ROUTE_ROUTE_META_HPP
#define WEBSERV_CORE_ROUTING_ROUTE_ROUTE_META_HPP

#include "../../../defs.hpp"

#include "../../../http/request.hpp"
#include "../../../util/optional.hpp"
#include "../../../util/refcounted.hpp"

namespace webserv {
    namespace core {

        class route_meta : public webserv::util::refcounted {
        protected:
            webserv::util::optional<std::set<webserv::http::http_method> >  _allowed_methods;

        public:
            route_meta();
            virtual ~route_meta();

            bool is_method_allowed(webserv::http::http_method method);

            route_meta* set_allowed_method(webserv::http::http_method method);
            route_meta* unset_allowed_method(webserv::http::http_method method);

        };

    }
}

#endif
