#include "ProducerConsumerMonitor.h"

int main() {
	ProducerConsumerMonitor monitor;
	
	Producer producer = Producer(&monitor);
	producer.start();
	
	Consumer consumer = Consumer(&monitor);
	consumer.start();
	
	Consumer anotherConsumer = Consumer(&monitor);
	anotherConsumer.start();
	
	producer.waitFor();
	consumer.waitFor();
	anotherConsumer.waitFor();
	
}