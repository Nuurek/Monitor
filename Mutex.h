#pragma once

#include <pthread.h>
#include <stdio.h>
#include <cstring>
#include <iostream>

class Mutex {
	pthread_mutex_t* mutex;
	
public:
	Mutex() noexcept;
	
	~Mutex() noexcept;
	
	int lock() noexcept;
	
	int unlock() noexcept;
	
	int wait() noexcept;
	
	int signal() noexcept;
};