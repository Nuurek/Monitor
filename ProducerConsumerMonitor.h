#pragma once

#include <unistd.h>
#include <sys/wait.h>

#include "Monitor.h"
#include "ConditionVariable.h"
#include "MonitorException.h"

const int maxNumberOfItems = 10;
const int startNumberOfItems = 5;

class ProducerConsumerMonitor : public Monitor {
	ConditionVariable full, empty;
	int count;
	
	int max = maxNumberOfItems;
	
	void enter();
	
	int remove();
	
public:
	Entry<void(ProducerConsumerMonitor*)> entryEnter;
	Entry<int(ProducerConsumerMonitor*)> entryRemove;

	ProducerConsumerMonitor() noexcept;
};

class Producer {
	ProducerConsumerMonitor* monitor;
	
	pthread_t producerThread;
	
	int counter = 0;
	
	public:
	Producer(ProducerConsumerMonitor* monitor) noexcept;
	
	void* produce(void);
	
	static void* notOOPProduce(void* producer);
	
	void start();
	
	void waitFor();
};

class Consumer {
	ProducerConsumerMonitor* monitor;
	pthread_t consumerThread;
	
	int counter = 0;
	
	public:
	Consumer(ProducerConsumerMonitor* monitor) noexcept;
	
	void* consume(void);
	
	static void* notOOPConsume(void* consumer);
	
	void start();
	
	void waitFor();
};