#include "ClassDeclarations.h"
#include <condition_variable>

static void func1(int num);
static void func2(int num);
static void func3(int num);
static void func4(int num);
static void func5(int num);

void Locks::lockExamples()
{
	//Three types of lock objects in the current standard library
		//std::lock_guard<> lck1();
		//std::unique_lock<> lck2();
		//std::shared_lock<std::mutex> lck3(); //Also a type of lock in C++14
			//Uses: #include <shared_mutex>

	//The above are templated classes
		//They accepted data types are of the various mutex objects in the standard library
			//Example:
			std::timed_mutex tmEx;
			std::lock_guard<std::timed_mutex> lgEx(tmEx);

	//This tutorial will focus on lock_guard and unique_lock as shared_lock can't be used in Visual Studio 2013

	//What are these locks for when the mutexes can lock themselves?
		//lock_guard<> acts as a nice wrapper if you want your mutex to be unlocked at the end of a function or something like that
		//unique_guard<> can do the same too, but is required for conditional variables from the <condition_variable> header file
		//Also, unique_lock<> and lock_guard<> both guarantee the mutex passed in will be unlocked when an exception is thrown



	//Lock_Guard<>:

	//A lock_guard<> is an object that manages a mutex object by keeping it always locked.
		//From: http://www.cplusplus.com/reference/mutex/lock_guard/
	//How to use std::lock_guard<>
		//well, lets use basic multithreading
	std::thread t1(func1, 1);
	std::thread t2(func1, 2);
	t1.join();
	t2.join();
	


	//Unique_Lock<>:

	//A unique lock is similar to a lock_guard<>, but it manages a mutex object in both the locked and unlocked states with sole ownership
	//How to use std::lock_guard<>
	
	//Example 1:
	std::thread t3(func2, 1);
	std::thread t4(func2, 2);
	t3.join();
	t4.join();

	//Example 2:
	std::thread t5(func3, 1);
	std::thread t6(func3, 2);
	t5.join();
	t6.join();

	//Example 3:
	std::thread t7(func4, 1);
	std::thread t8(func5, 2);
	t7.join();
	t8.join();
}

//This will be used in all the later examples
static std::mutex mtx;

//if you want to see what it is like without the lock_guard<> and the unique_lock<>, comment them out and increase the number of interations of the for loops
	//Increasing the interations will exaggerate the non-linear behaviour of the threads

#pragma region lock_guard<> Example
void func1(int num)
{
	//The lock_guard<> below locks mtx and since lock_guard<> guarantees unlocking on destruction, once the function is done the mutex will unlock
		//lock_guard<> locks the mutex passed in, in the lock_guard<>'s constructor
	std::lock_guard<std::mutex> lck(mtx);
	//lock_guard<> has no member functions other than its constructor and destructor
	for (int i = 0; i < 20; i++)
	{
		printf("Thread: %d, Just printing to the screen: %d\n", num, i);
	}

	printf("\n");
}	//here is where lck will be destroyed and mtx will unlock, allowing t2 to access the for loop and printf statement
#pragma endregion

#pragma region unique_lock<> Examples

#pragma region unique_lock<> Example 1
//A unique_lock<> has the same guarantees to unlock on destruction, so we can use it exactly like a lock_guard<> and below I give an example of that
	//A unique_lock<> has more overhead and thus the below example is a poor use of a unique_lock<>
void func2(int num)
{
	//The unique_lock<> below locks mtx and since unique_lock<> guarantees unlocking on destruction, once the function is done the mutex will unlock
		//The unique_lock<> doesn't have to lock the mutex passed in, in its constructor, but in this case it does
	std::unique_lock<std::mutex> lck(mtx);
	for (int i = 0; i < 20; i++)
	{
		printf("Thread: %d, Just printing to the screen: %d\n", num, i);
	}

	printf("\n");
}	//here is where lck will be destroyed and mtx will unlock, allowing t2 to access the for loop and printf statement
#pragma endregion

#pragma region unique_lock<> Example 2
std::timed_mutex tm;
//A unique_lock<> has some member functions that lock_guard<> does not
void func3(int num)
{
	//since unique_lock can take all of the various standard library mutex objects, it has those functions as well
	std::unique_lock<std::timed_mutex> lck(tm);
	//An example of the unique_lock<> not locking the mutex in its constructor
	tm.try_lock_for(std::chrono::seconds(1));

	//Also, you can check on the lock's ownership with:
	if (lck.owns_lock())
	{
		printf("Thread %d Owns the Lock\n", num);
		lck.unlock();
	}
	//Or
	/*if (lck)
	{
		printf("Thread %d Owns the Lock\n", num);
		lck.unlock();
	}*/
}
#pragma endregion

#pragma region unique_lock<> Example 3
//The third use of unique_lock<> is its use with condition variables
std::condition_variable cv;

void func4(int num)
{
	std::unique_lock<std::mutex> lck(mtx);
	//The wait function requires a unique_lock<>
		//Blocks this threads execution until notified
		//wait() unlocks the lock and then when it is notified to continue, relocks the lock
	cv.wait(lck);
	for (int i = 0; i < 20; i++)
	{
		printf("Thread: %d, Just printing to the screen: %d\n", num, i);
	}

	printf("\n");
}

void func5(int num)
{
	std::unique_lock<std::mutex> lck(mtx);
	for (int i = 0; i < 20; i++)
	{
		printf("Thread: %d, Just printing to the screen: %d\n", num, i);
	}

	printf("\n");
	//notify the other thread that this thread is done
	cv.notify_one();
}
#pragma endregion

//Unique lock has another use dealing with move semantics
	//it can be returned from a function without releasing the lock
//For more you can read: https://www.justsoftwaresolutions.co.uk/threading/locks-mutexes-semaphores.html
#pragma endregion