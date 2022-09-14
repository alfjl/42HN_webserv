#ifndef WEBSERV_HTTP_STATE_STATE_MACHINE_HPP
#define WEBSERV_HTTP_STATE_STATE_MACHINE_HPP

#include "../../defs.hpp"
#include "state.hpp"

namespace webserv {
    namespace http {

        template<typename T>
        class state_machine {
        private:
            T           *m_pOwner;
            state<T>    *m_pCurrentState;
            bool        m_firstRun;

        public:
            state_machine() {
                m_firstRun = true;
                std::cout << "State machine created!" << std::endl;
                }
            ~state_machine() { std::cout << "State machine destroyed!" << std::endl; }
            void init(T *pOwner, state<T> *initial_state);
            void update();
            void change_state(state<T> *new_state);

        }; // class state_machine

template<typename T>
inline void state_machine<T>::init(T *pOwner, state<T> *initial_state) {
    m_pOwner = pOwner;
    m_pCurrentState = initial_state;
    std::cout << "State machine ready!\n" << std::endl;
}

template<typename T>
inline void state_machine<T>::update() {
    if (m_firstRun) {
        m_firstRun = false;
        m_pCurrentState->Enter(m_pOwner);
    }
    m_pCurrentState->Execute(m_pOwner);
    std::cout << "State machine updated!\n" << std::endl;
}

template<typename T>
inline void state_machine<T>::change_state(state<T> *new_state) {
    m_pCurrentState->Exit(m_pOwner);
    m_pCurrentState = new_state;
    m_pCurrentState->Enter(m_pOwner);
}

    } // namespace http
} // namespace webserve

#endif