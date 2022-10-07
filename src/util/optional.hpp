#ifndef WEBSERV_UTIL_OPTIONAL_HPP
#define WEBSERV_UTIL_OPTIONAL_HPP

namespace webserv {
    namespace util {

        template<typename T>
        class optional {
            T    _value;
            bool _enabled;
        public:
            optional() : _enabled(false) {}
            optional(T value) :  _value(value), _enabled(true) {}

            bool enabled() const { return _enabled; }

            T& value() { return _value; }
            T& value() const { return _value; }

            void disable() { _enabled = false; }
            void enable(T value) { _enabled = true; _value = value; }
        };

    }
}

#endif