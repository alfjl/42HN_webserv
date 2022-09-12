#ifndef WEBSERV_PAL_CPP_GUARDED_HPP
#define WEBSERV_PAL_CPP_GUARDED_HPP

#include "../../defs.hpp"
#include "../../threading/threading.hpp"

/*
 * Based on implementation of std::shared_ptr and inspired by
 *
 *   https://cppsecrets.com/users/41129711010797106994610011511264103109971051084699111109/Write-your-own-shared-pointer.php
 * 
 * But using a payload struct, for better self regulation and safer memory management
 * 
 *                                            - alanghan
 */

namespace webserv {
    namespace pal {
        namespace cpp {

    template <typename T>
    class guarded {

    public:
        class borrow {

        private:
            guarded&    _guard;

        public:
            borrow(guarded& guard) : _guard(guard) {
                _guard._protection.lock();
            }

            ~borrow() { _guard._protection.unlock(); }

            T&  operator*() const { return *(_guard.base()); }
            T*  operator->() const { return _guard.base(); }

            T&  getValue() { return _guard.getValue(); }
            T&  getValue() const { return _guard.getValue(); }

        }; // class borrow

    private:
        friend class borrow;

        T                           _value;
        webserv::threading::mutex   _protection;

    public:
        guarded(T value) { _value = value; }

        ~guarded() {
        }

    private:
        T&  getValue() { return _value; }
        T&  getValue() const { return _value; }

    public:
        borrow  get_borrow() { return (borrow(*this)); }
        T*      base() const { return *(_value); }

    }; // class guarded

        } // namespace cpp
    } // namespace pal
} // namespace webserv

#endif
