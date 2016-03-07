#include "Monitor.h"
	
void Monitor::lock() noexcept {
	monitorMutex.lock();		//If other thread is in monitor then thread has to wait.
}

void Monitor::unlock() noexcept {					//Thread can unlock monitor for another thread
	if (nextCount > 0) { 		//if it was someone waiting because of signal from some condition variable or...
		nextMutex.unlock();
	} else {					//...if it was someone just locked on waiting for monitor.
		monitorMutex.unlock();	
	}
}