#include "AtomicCounter.h"

AtomicCounter::AtomicCounter() noexcept {
	counter = static_cast<int*>(malloc(sizeof(int)));
	if (counter == nullptr) {
		std::cerr << "Failed at allocating memory for AtomicCounter\n" << strerror(errno) << "\n";
		return;
	}
	*counter = 0;
}

AtomicCounter::AtomicCounter(int i) noexcept : AtomicCounter() {
	*counter = i;
}

AtomicCounter::~AtomicCounter() noexcept {
	free(counter);
}

AtomicCounter& AtomicCounter::operator++() noexcept {
	mutex.lock();
	++(*counter);
	mutex.unlock();
	return *this;
}

AtomicCounter& AtomicCounter::operator--() noexcept {
	mutex.lock();
	--(*counter);
	mutex.unlock();
	return *this;
}

AtomicCounter::operator int() const noexcept {
	return *counter;
}

bool AtomicCounter::operator>(const int& rhs) const noexcept {
	return *counter > rhs;
}

bool AtomicCounter::operator<(const int& rhs) const noexcept {
	return *counter < rhs;
}

bool AtomicCounter::operator==(const int& rhs) const noexcept {
	return *counter == rhs;
}

bool AtomicCounter::operator>=(const int& rhs) const noexcept {
	return (*counter > rhs) || (*counter == rhs);
}

bool AtomicCounter::operator<=(const int& rhs) const noexcept {
	return (*counter < rhs) || (*counter == rhs);
}