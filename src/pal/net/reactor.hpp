#ifndef WEBSERV_PAL_NET_REACTOR_HPP
#define WEBSERV_PAL_NET_REACTOR_HPP

#include "../../defs.hpp"
#include "../../util/wrapped_queue.hpp"

namespace webserv {
    namespace pal {
        namespace net {

            class reactor {
            public:
                virtual ~reactor();
                
                virtual void increment_refcount() = 0;
                virtual void decrement_refcount() = 0;

                virtual webserv::util::wrapped_queue& get_input() = 0;
                virtual webserv::util::wrapped_queue& get_output() = 0;

                virtual void react_close() = 0;
                virtual bool is_closed() = 0;
            };

        }
    }
}

#endif
