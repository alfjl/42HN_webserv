#ifndef WEBSERV_HTTP_STATE_COOL_STATES_HPP
#define WEBSERV_HTTP_STATE_COOL_STATES_HPP

#include "../../defs.hpp"
#include "state.hpp"
#include "a_cool_state_machine.hpp" // not in Video

namespace webserv {
    namespace http {

        class start_state : public state<class a_cool_state_machine> {

        public:
            void Enter(a_cool_state_machine *pOwner) {
                std::cout << "Enter Start State\n" << std::endl;
            }
            void Execute(a_cool_state_machine *pOwner);
            void Exit(a_cool_state_machine *pOwner) {
                std::cout << "Exit from Start State\n" << std::endl;
            }

        }; // class start_state

        class state1 : public state<class a_cool_state_machine> {

        public:
            void Enter(a_cool_state_machine *pOwner) {
                std::cout << "Enter State1\n" << std::endl;
            }
            void Execute(a_cool_state_machine *pOwner);
            void Exit(a_cool_state_machine *pOwner) {
                std::cout << "Exit from State1\n" << std::endl;
            }

        }; // class state1

        class state2 : public state<class a_cool_state_machine> {

        public:
            void Enter(a_cool_state_machine *pOwner) {
                std::cout << "Enter State2\n" << std::endl;
            }
            void Execute(a_cool_state_machine *pOwner);
            void Exit(a_cool_state_machine *pOwner) {
                std::cout << "Exit from State2\n" << std::endl;
            }

        }; // class state2

        class stateN : public state<class a_cool_state_machine> {

        public:
            void Enter(a_cool_state_machine *pOwner) {
                std::cout << "Enter StateN\n" << std::endl;
            }
            void Execute(a_cool_state_machine *pOwner);
            void Exit(a_cool_state_machine *pOwner) {
                std::cout << "Exit from StateN\n" << std::endl;
            }

        }; // class stateN

    } // namespace http
} // namespace webserve

#endif