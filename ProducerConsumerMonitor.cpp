#include "ProducerConsumerMonitor.h"

void ProducerConsumerMonitor::enter() {
	if (count > max) {
		throw MonitorException(this, &empty);
	}
	std::cout << "Count on enter: " << count << "\n";
	if (count == max) {
		std::cout << "Waiting for free space\n";
		full.wait();
	}
	std::cout << "Entered item\n";
	++count;
	std::cout << "Count after entering: " << count << "\n";
	if (count > 0) {
		empty.signal();
	}
}

int ProducerConsumerMonitor::remove() {
	if (count < 0) {
		throw MonitorException(this, &full);
	}
	std::cout << "Count on remove " << count << "\n";
	if (count == 0) {
		std::cout << "Waiting for item\n";
		empty.wait();
	}
	std::cout << "Removed item\n";
	--count;
	std::cout << "Count after removing: " << count << "\n";
	if (count < max) {
		full.signal();
	}
	return 1;
}

ProducerConsumerMonitor::ProducerConsumerMonitor() noexcept : Monitor(), full(this), empty(this),
	entryEnter(this, std::function<void(ProducerConsumerMonitor*)>(&ProducerConsumerMonitor::enter)),
	entryRemove(this, std::function<int(ProducerConsumerMonitor*)>(&ProducerConsumerMonitor::remove))
{
	count = startNumberOfItems;
}


Producer::Producer(ProducerConsumerMonitor* monitor) noexcept {
	this->monitor = monitor;
}

void* Producer::produce(void) {
	while(counter < 10) {
		++counter;
		std::cout << "Producing item " << counter << "\n";
		sleep(1); //PRODUCING
		std::cout << "Entering item " << counter << "\n";
		monitor->entryEnter(monitor);
		std::cout << "Item entered " << counter << "\n";
	}
	return nullptr;
}

void* Producer::notOOPProduce(void* producer) {
	return ((Producer*)producer)->produce();
}

void Producer::start() {
	pthread_create(&producerThread, NULL, notOOPProduce, this);
}

void Producer::waitFor() {
	pthread_join(producerThread, NULL);
}

Consumer::Consumer(ProducerConsumerMonitor* monitor) noexcept {
	this->monitor = monitor;
}

void* Consumer::consume(void) {
	while(counter < 5) {
		++counter;
		std::cout << "Removing item " << counter << "\n";
		monitor->entryRemove(monitor);
		std::cout << "Consuming item " << counter << "\n";
		sleep(1); //CONSUMING
		std::cout << "Item consumed " << counter << "\n";
	}
	return nullptr;
}

void* Consumer::notOOPConsume(void* consumer) {
	return ((Consumer*)consumer)->consume();
}

void Consumer::start() {
	pthread_create(&consumerThread, NULL, notOOPConsume, this);
}

void Consumer::waitFor() {
	pthread_join(consumerThread, NULL);
}