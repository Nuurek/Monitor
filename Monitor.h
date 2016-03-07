#pragma once

#include <functional>
#include <type_traits>

#include "Mutex.h"
#include "AtomicCounter.h"

class Monitor {
public:
	Mutex monitorMutex;
	Mutex nextMutex;
	
	AtomicCounter nextCount;
	
	void lock() noexcept;
	
	void unlock() noexcept;
};

template <class FunctionType> 
class Entry {
	std::function<FunctionType> internalFunction;
	
	Monitor* monitor;
	
public:
	Entry(Monitor* monitor, const std::function<FunctionType> function) noexcept :
		internalFunction(function) {
			this->monitor = monitor;
	}

	template<class... Arguments, bool EnableBool = true>
	typename std::enable_if<
		std::is_void<
			typename std::function<
				FunctionType
			>::result_type
		>::value && EnableBool, 
		void
	>::type
	operator()(Arguments... arguments) noexcept {
		monitor->lock();
		internalFunction(arguments...);
		monitor->unlock();
	}
	
	template<class... Arguments, bool EnableBool = true>
	typename std::enable_if<
		not std::is_void<
			typename std::function<
				FunctionType
			>::result_type
		>::value && EnableBool, 
		typename std::function<
			FunctionType
		>::result_type
	>::type
	operator()(Arguments... arguments) noexcept {
		monitor->lock();
		auto result = internalFunction(arguments...);
		monitor->unlock();
		return result;
	}
};