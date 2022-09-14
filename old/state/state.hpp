#ifndef WEBSERV_HTTP_STATE_STATE_HPP
#define WEBSERV_HTTP_STATE_STATE_HPP

#include "../../defs.hpp"

namespace webserv {
    namespace http {

        template<typename T>
        class state {

        public:
            virtual ~state(){}
            virtual void Enter(T *pOwner) = 0;
            virtual void Execute(T *pOwner) = 0;
            virtual void Exit(T *pOwner) = 0;

        }; // class state

    } // namespace http
} // namespace webserve

#endif
