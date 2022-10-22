#ifndef WEBSERV_CORE_ROUTING_ROUTE_TRANSLATION_FUNCTION_HPP
#define WEBSERV_CORE_ROUTING_ROUTE_TRANSLATION_FUNCTION_HPP

namespace webserv {
    namespace core {

        struct match_info;

        class translation_function {
        public:
            translation_function();
            virtual ~translation_function();

            virtual bool convert(match_info& meta) = 0;
        };

        class zero_translation_function : public translation_function {
        public:
            bool convert(match_info& meta);
        };

        class relative_translation_function : public translation_function {
        public:
            bool convert(match_info& meta);
        };

    }
}

#endif
