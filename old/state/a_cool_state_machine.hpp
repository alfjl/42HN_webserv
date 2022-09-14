#ifndef WEBSERV_HTTP_STATE_A_COOL_STATE_MACHINE_HPP
#define WEBSERV_HTTP_STATE_A_COOL_STATE_MACHINE_HPP

#include "../../defs.hpp"
#include "state_machine.hpp"

namespace webserv {
    namespace http {

        class a_cool_state_machine : public state_machine<a_cool_state_machine> {
        private:
            state<a_cool_state_machine> *m_start_state;
            state<a_cool_state_machine> *m_state1;
            state<a_cool_state_machine> *m_state2;
            state<a_cool_state_machine> *m_stateN;

            bool                        m_done;
        public:
            a_cool_state_machine();
            ~a_cool_state_machine();
            void update();
            void done() {
                m_done = true;
            }
            bool has_done() {
                return m_done;
            }

            friend class start_state;
            friend class state1;
            friend class state2;
            friend class stateN;

        }; // class a_cool_state_machine

    } // namespace http
} // namespace webserve

#endif
