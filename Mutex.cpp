#include "Mutex.h"

Mutex::Mutex() noexcept {
	mutex = static_cast<pthread_mutex_t*>(malloc(sizeof(pthread_mutex_t)));
	if (mutex == nullptr) {
		std::cerr << "Failed at allocating memory for Mutex: " << strerror(errno) << "\n";
		return;
	}
	int status = pthread_mutex_init(mutex, NULL);
	if (status != 0) {
		std::cerr << "Failed at initiating Mutex: " << strerror(errno) << "\n";
		return;
	}
}

Mutex::~Mutex() noexcept {
	int status = pthread_mutex_destroy(mutex);
	if (status == -1) {
		std::cerr << "Failed at destroying Mutex: " << strerror(errno) << "\n";
	}

	free(mutex);
}

int Mutex::lock() noexcept {
	int status = pthread_mutex_lock(mutex);
	if (status != 0) {
		std::cerr << "Failed at locking Mutex: " << strerror(errno) << "\n";
		return status;
	} else {
		return 0;
	}
}

int Mutex::unlock() noexcept {
	int status = pthread_mutex_unlock(mutex);
	if (status != 0) {
		std::cerr << "Failed at unlocking Mutex: " << strerror(errno) << "\n";
		return status;
	} else {
		return 0;
	}
}

int Mutex::wait() noexcept {
	return lock();
}

int Mutex::signal() noexcept {
	return unlock();
}