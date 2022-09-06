#ifndef WEBSERV_PAL_CPP_SHARED_PTR_HPP
#define WEBSERV_PAL_CPP_SHARED_PTR_HPP

#include "../../defs.hpp"
#include "../../threading/threading.hpp"

/*
 * Based on implementation of std::shared_ptr and heavily inspired by
 *
 *   https://cppsecrets.com/users/41129711010797106994610011511264103109971051084699111109/Write-your-own-shared-pointer.php
 * 
 *                                            - alanghan
 */

namespace webserv {
    namespace pal {
        namespace cpp {
    /*
     * Maintains the number of shared_owners
     * (number of pointers pointing to member 'ptr' in our shared_ptr class)
     */
    class shared_count {

    private:
        unsigned long				shared_owners;
		webserv::threading::mutex	the_mutex;
    public:

        // Default constructor
        shared_count();

    protected:
        // Default destructor
        virtual ~shared_count();

    public:
        // Increment reference count
        void increment();

        // Decrement reference count
        void decrement();

        // Get reference count
        long getCount();

    }; // class shared_count


    /*
     * Own implementation of the std::shared_ptr to be usable in our std=c++98 Standard project.
     * Keeps track of the number of owners pointing on the same ptr.
     * This class will automatically allocate and deallocate memory.
     */
    template<typename T>
    class shared_ptr {

    public:
        typedef T element_type;

    private:
        element_type*   ptr; // shared pointer
        shared_count*   cnt; // number of owners of 'ptr'
        webserv::pal::

    public:
        // Parametarized Constructor
        shared_ptr(T* ptrValue = webserv::nullptr_t);

        // Copy constructor
        shared_ptr(const shared_ptr<T>& other);

        // Destructor
        ~shared_ptr();

        // Overload operator * to get class object
        T& operator*();

        // Overload operator -> to access class member functions
        T* operator->();

        // Assignment operator
        shared_ptr<T>& operator=(const shared_ptr<T>& other);

    }; // class shared_ptr

	// Parametarized Constructor
    template<typename T>
	shared_ptr<T>::shared_ptr(T* ptrValue) : ptr(ptrValue), cnt(0) {
		this->cnt = new shared_count();
		if (ptrValue)
        {
            this->cnt->increment();
        }
    }

	// Copy constructor
	// DO NOT ALLOCATE NEW MEMORY IN COPY CONSTRUCTOR
	// Do shallow copy of the data and increment refence count
    template<typename T>
	shared_ptr<T>::shared_ptr(const shared_ptr<T>& other) : ptr(other.ptr), cnt(other.cnt) {
		this->cnt->increment();
	}

	// Destructor
	// It will play an important role in shared pointer
	// We use shallow copy instead of deep copy, so destructor will de-allocate
    // the memory only when reference count reaches '0'
	// We can't directly free the memory without adding check of reference
	// count, otherwise program will crash
	// 1. Decrement reference count
	// 2. Check if reference count reaches to zero, then delete the memory
    template<typename T>
	shared_ptr<T>::~shared_ptr() {
		this->cnt->decrement();
		if (cnt->getCount() == 0) {

			// Use Safe delete to avoid crash and dangling pointer
			if(this->ptr) {
				delete this->ptr;
				this->ptr = 0;
			}

			// Use Safe delete to avoid crash and dangling pointer
			if(this->cnt) {
				delete this->cnt;
				this->cnt = 0;
			}
		}
	}

	// Overload operator * to get class object
    template<typename T>
	T& shared_ptr<T>::operator*() {
		return *(this->ptr);
	}

	// Overload operator -> to access class member functions
    template<typename T>
	T* shared_ptr<T>::operator->() {
		return this->ptr;
	}

	// Assignment operator
	// DO NOT ALLOCATE NEW MEMORY WHILE OVERLOADING ASSIGNMENT OPERATOR
	// 1. Delete previously allocated memory with reference count check
	// 2. Do shallow copy
	// 3. increment reference count
    template<typename T>
	shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& other) {

		// Avoid self assignment
		if (this != &other) {
			this->cnt->decrement();
			if (this->cnt->getCount() == 0) {

				// Use Safe delete to avoid crash and dangling pointer
				if(this->ptr) {
					delete this->ptr;
					this->ptr = 0;
				}

				// Use Safe delete to avoid crash and dangling pointer
				if(this->cnt) {
					delete this->cnt;
					this->cnt = 0;
				}
			}

			// Copy the data and cnt pointer
			// and increment the cnt m_Count
			this->ptr = other.ptr;
			this->cnt = other.cnt;
			this->cnt->increment();
		}
		return *this;
	}

    make_shared() {

    }

        } // namespace cpp
    } // namespace pal
} // namespace webserv

#endif
