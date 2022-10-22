#ifndef WEBSERV_UTIL_CONNECTION_HPP
#define WEBSERV_UTIL_CONNECTION_HPP

#include "../defs.hpp"

#include "../pal/net/reactor.hpp"
#include "../util/refcounted.hpp"

#include "iflow.hpp"
#include "oflow.hpp"
#include "wrapped_queue.hpp"

namespace webserv {
    namespace util {

        class connection : public virtual webserv::pal::net::reactor, public virtual webserv::util::refcounted {
            oflow             out;
            std::ostream      ostream;
            wrapped_queue     input_buffer;
            wrapped_queue     output_buffer;
            bool              closed;

        public:
            connection();
            ~connection();

            wrapped_queue& get_input();
            wrapped_queue& get_output();
            std::ostream&  get_ostream();

            void close();
            bool is_closed();

            void notify_about_close();
        };

    }
}

#endif
