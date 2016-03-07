#pragma once

#include <pthread.h>
#include <cstring>

#include "Monitor.h"

class ConditionVariable {
	Mutex mutex;
	
	Monitor* monitor;
	
	AtomicCounter count;
	
public:
	ConditionVariable(Monitor* monitor) noexcept;
	
	void wait() noexcept;
	
	void signal() noexcept;
};
