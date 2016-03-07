#pragma once

#include <exception>
#include <string>

#include "ConditionVariable.h"

class MonitorException : public std::exception {
	const std::string exceptionMessage = "Exception from monitor. All locks passed in arguments were unlocked.";
	
	template <typename Cond>
	void unlock(Cond* conditionVariable) noexcept {
		conditionVariable->signal();
	}
	
	template <typename FirstCond, typename... RestConds>
	void unlock(FirstCond* firstCond, RestConds*... conditionVariables) noexcept {
		firstCond->signal();
		unlock(conditionVariables...);
	}
	
public:
	template <typename... ConditionVariables>
	MonitorException(Monitor* monitor, ConditionVariables*... conditionVariables) {
		monitor->unlock();
		unlock(conditionVariables...);
	}
	
	const char * what() const noexcept{
		return exceptionMessage.c_str();
	}
};