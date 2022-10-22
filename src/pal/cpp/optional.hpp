#ifndef WEBSERV_UTIL_OPTIONAL_HPP
#define WEBSERV_UTIL_OPTIONAL_HPP

namespace webserv {
    namespace pal {
        namespace cpp {

            template<typename T>
            class optional {
                T    _value;
                bool _enabled;

            public:
                optional() : _enabled(false) {}
                optional(T value) :  _value(value), _enabled(true) {}

                bool enabled() const { return _enabled; }

                T& value() { return _value; }
                const T& value() const { return _value; }

                void disable() { _enabled = false; }
                void enable() { _enabled = true; }
                void enable(T value) { _enabled = true; _value = value; }
            };

        }
    }
}

#endif
