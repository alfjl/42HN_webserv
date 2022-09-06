#ifndef WEBSERV_PAL_CPP_SHARED_PTR_HPP
#define WEBSERV_PAL_CPP_SHARED_PTR_HPP

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

    /*
     * Maintains the mutex, count of shared owners
     * (number of pointers pointing to member 'ptr')
     * and the object pointed to.
	 */
    template<typename T>
    class shared_ptr_payload {

    public:
        typedef T element_type;

    private:
        element_type*   			ptr; // shared pointer
        unsigned long				count; // number of owners of 'ptr'
		webserv::threading::mutex	the_mutex;

    public:

        // Default constructor
        shared_ptr_payload(T* ptrValue);

    protected:
        // Default destructor
        ~shared_ptr_payload();

    public:
        // Increment reference count
        void increment();

        // Decrement reference count
        void decrement();

        // Get reference count
        long getCount();

        T* base() const { return ptr; }

    }; // class shared_ptr_payload

	/*
	 * Default constructor
	 */
    template<typename T>
	shared_ptr_payload<T>::shared_ptr_payload(T* ptrValue) : ptr(ptrValue), count(0) {
		if (ptrValue != NULL)
            this->increment();
	}

	/*
	 * Default destructor
	 */
    template<typename T>
	shared_ptr_payload<T>::~shared_ptr_payload() {

		// Use Safe delete to avoid crash and dangling pointer
		if (this->ptr) {
			delete this->ptr;
			this->ptr = NULL;
		}
	}

	/*
	 * Increment reference count
	 */
    template<typename T>
	void shared_ptr_payload<T>::increment() {
		the_mutex.lock();
		++(this->count);
		the_mutex.unlock();
	}

	/*
	 * Decrement reference count
	 */
    template<typename T>
	void shared_ptr_payload<T>::decrement() {
		the_mutex.lock();
		--(this->count);
		the_mutex.unlock();
		if (count == 0) {
			delete this;
		}
	}

	/*
	 * Get reference count
	 */
    template<typename T>
	long shared_ptr_payload<T>::getCount() {
		return (this->count);
	}


    /*
     * Own implementation of the std::shared_ptr to be usable in our std=c++98 Standard project.
     * Keeps track of the number of owners pointing on the same ptr.
     * This class will automatically allocate and deallocate memory, via it's payload struct.
     */
    template<typename T>
    class shared_ptr {

	private:
        shared_ptr_payload<T>*   payload; // shared pointer

    public:
        // Parametarized Constructor
        shared_ptr(T* ptrValue = NULL);

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

	/*
	 * Parametarized Constructor
	 */
    template<typename T>
	shared_ptr<T>::shared_ptr(T* ptrValue) {
		this->payload = new shared_ptr_payload<T>(ptrValue);
    }

	/*
	 * Copy constructor
	 * DO NOT ALLOCATE NEW MEMORY IN COPY CONSTRUCTOR
	 * Do shallow copy of the payload struct and increment payload count
	 */
	template<typename T>
	shared_ptr<T>::shared_ptr(const shared_ptr<T>& other) {
		this->payload = other.payload;
		this->payload->increment();
	}

	/*
	 * Destructor
	 * It will play an important role in shared pointer
	 * We use shallow copy instead of deep copy, so payload destructor will
	 * de-allocate the memory only when payload count reaches '0'
	 * We can't directly free the memory without adding check of payload count, 
	 * otherwise program will crash
	 * 1. Decrement reference count
	 * 2. Check if reference count reaches to zero, then delete the memory
	 */
	template<typename T>
	shared_ptr<T>::~shared_ptr() {
		this->payload->decrement();
		
		// // Use Safe delete to avoid crash and dangling pointer
		// if (this->getCount() == 0) {
		// 	delete this->payload;
		// }
	}

	/*
	 * Overload operator * to get class object
	 */
	template<typename T>
	T& shared_ptr<T>::operator*() {
		return *(this->payload->base());
	}

	/*
	 * Overload operator -> to access class member functions
	 */
	template<typename T>
	T* shared_ptr<T>::operator->() {
		return this->payload->base();
	}

	/*
	 * Assignment operator
	 * DO NOT ALLOCATE NEW MEMORY WHILE OVERLOADING ASSIGNMENT OPERATOR
	 * 1. Decrement count of pointers
	 * 2. Do shallow copy of other's payload struct
	 * 3. increment reference count
	 */
	template<typename T>
	shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& other) {

		// Avoid self assignment
		if (this != &other) {
			this->payload->decrement();

			// Copy the payload link
			// and increment the count payload count
			this->payload = other.payload;
			this->payload->increment();
		}
		return *this;
	}

	/*
	 * Allocates and constructs an object of type T
	 * and returns an object of type shared_ptr<T>
	 * that owns and stores a pointer to it (with a use count of 1).
     */
	template<typename T>
    shared_ptr<T> wrap_shared(T* value) {
		shared_ptr<T>	ptr(value);
		return ptr;
    }

        } // namespace cpp
    } // namespace pal
} // namespace webserv

#endif
