#include "ConditionVariable.h"

ConditionVariable::ConditionVariable(Monitor* monitor) noexcept {
	int status = mutex.lock();
	if (status != 0) {
		std::cerr << "Failed at constructing ConditionVariable: " << strerror(errno) << "\n";
	}

	this->monitor = monitor;
}

void ConditionVariable::wait() noexcept {
	++count;							//One more thread waiting for signal.
										//Now this thread is waiting so it can unlock monitor...
	if (monitor->nextCount > 0) {		
		monitor->nextMutex.unlock();	//...for some other thread waiting on queued up signalled threads or...
	} else {
		monitor->monitorMutex.unlock();	//...for some other thread just waiting for access to monitor.
	}

	mutex.lock();						//Wait for signal on this condition variable.

	--count;							//One thread less waiting for signal.
}

void ConditionVariable::signal() noexcept {
	if (count > 0) {					//If some threads are waiting for signal then...
		++(monitor->nextCount);			//...this thread has to increment monitor's counter of queued up threads,...

		mutex.unlock();					//...pass some other thread that was waiting for signal,...
		monitor->nextMutex.lock();		//...wait by itself for someone leaving monitor...

		--(monitor->nextCount);			//...and in the end decrement monitor's counter of queued up threads.
	}
}