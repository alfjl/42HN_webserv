#include "shared_ptr.hpp"

namespace webserv {
    namespace pal {
        namespace cpp {

	/*
	 * class shared_count
	 */

	// Default constructor
	shared_count::shared_count() : shared_owners(0) {

	}

	// Increment reference count
	void shared_count::increment() {
		mutex.lock();
		++(this->shared_owners);
		mutex.unlock();
	}

	// Decrement reference count
	void shared_count::decrement() {
		mutex.lock();
		--(this->shared_owners);
		mutex.unlock();
	}

	// Get reference count
	long shared_count::getCount() {
		return (this->shared_owners);
	}

        } // namespace cpp
    } // namespace pal
} // namespace webserv
