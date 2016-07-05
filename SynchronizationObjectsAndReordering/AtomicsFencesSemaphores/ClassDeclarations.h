#pragma once
#include <iostream>
#include <thread>
#include <mutex>

/*class Reordering
{
public:
void basicReordering();
};*/

class Fences
{
public:
	void basicFenceExample();
};

class Atomics
{
public:
	void basics();
};

class Semaphores
{
public:
	int p;
};

class Mutexes
{
public:
	void mutexExamples();
};

class Locks
{
public:
	void lockExamples();
};
