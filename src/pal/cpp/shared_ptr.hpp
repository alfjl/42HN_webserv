#ifndef WEBSERV_PAL_CPP_SHARED_PTR_HPP
#define WEBSERV_PAL_CPP_SHARED_PTR_HPP

#include "../../defs.hpp"

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

            template<typename T>
            class shared_ptr {
            private:
                class core {
                    unsigned int  refcount;
                    T*            ptr;
                public:
                    template<typename T2>
                    core(T2* _ptr) : refcount(0), ptr(_ptr) {
                        // std::cout << this << " gets created " << std::endl;
                    }

                    ~core() {
                        if (ptr != NULL) {
                            delete ptr;
                        }
                    }

                    void increment() {
                        refcount++;
                        // std::cout << this << " gets incremented to " << refcount << std::endl;
                    }

                    void decrement() {
                        if (refcount == 0) {
                            // std::cout << this << " is at zero!" << std::endl;
                            delete this;
                        } else {
                            refcount--;
                            // std::cout << this << " gets decremented to " << refcount << std::endl;
                        }
                    }

                    T* get_ptr() const { return ptr; }
                };

                core* the_core;

            public:
                shared_ptr() {
                    // std::cout << "+ shared_ptr(NULL): " << this << std::endl;
                    the_core = new core((T*) NULL);
                }

                template<typename T2>
                explicit shared_ptr(T2* ptr) {
                    // std::cout << "+ shared_ptr(p): " << this << std::endl;
                    the_core = new core(ptr);
                }

                template<typename T2>
                shared_ptr(const shared_ptr<T2>& other) {
                    // std::cout << "+ shared_ptr(&): " << this << std::endl;
                    the_core = (core*) other.get_core();
                    the_core->increment();
                }

                template<typename T2>
                shared_ptr(shared_ptr<T2>& other) {
                    // std::cout << "! shared_ptr(&): " << this << std::endl;
                    the_core = (core*) other.get_core();
                    the_core->increment();
                }

                ~shared_ptr() {
                    // std::cout << "+ ~shared_ptr(): " << this << std::endl;
                    the_core->decrement();
                }

                shared_ptr& operator=(const shared_ptr& other) {
                    // std::cout << "+ shared_ptr(=): " << this << std::endl;
                    core* c = the_core;

                    if (this != &other) {
                        the_core = other.get_core();
                        the_core->increment();
                        c->decrement();
                    }

                    return *this;
                }

                core* get_core() const { return the_core; }
                T*    get() const { return get_core()->get_ptr(); }

                T& operator*() { return *(get()); }
                T* operator->() { return get(); }
            };
            
            template<typename T>
            shared_ptr<T> wrap_shared(T* value) {
                shared_ptr<T>   ptr(value);
                return ptr;
            }

        } // namespace cpp
    } // namespace pal
} // namespace webserv

#endif
