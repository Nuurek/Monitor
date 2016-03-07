#pragma once

#include "Mutex.h"

class AtomicCounter {
	int* counter;
	Mutex mutex;
	
public:
	AtomicCounter() noexcept;
	
	AtomicCounter(int i) noexcept;
	
	~AtomicCounter() noexcept;

	AtomicCounter& operator++() noexcept;
	
	AtomicCounter& operator--() noexcept;
	
	operator int() const noexcept;
	
	bool operator>(const int& rhs) const noexcept;
	
	bool operator<(const int& rhs) const noexcept;
	
	bool operator==(const int& rhs) const noexcept;
	
	bool operator>=(const int& rhs) const noexcept;
	
	bool operator<=(const int& rhs) const noexcept;
};