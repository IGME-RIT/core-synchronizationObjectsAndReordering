#include "ClassDeclarations.h"
#include <chrono>
#include <vector>

static void func(int num);
static void func2(int num, int threadNum);

void Mutexes::mutexExamples()
{
	//As you know a mutex is an object that allows you to control access to sections of multithreaded code
	//There is more than one type of mutex though
	//The C++ standard library currently defines 5 types of mutexes
	//They are:
		//std::mutex
		//std::timed mutex
		//std::recursive_mutex	
		//std::recursive_timed_mutex
		//std::shared_timed_mutex - Visual Studio could not find the file <shared_mutex>, so I will talk about this briefly

#pragma region Mutex
	//Below is a basic mutex
	std::mutex mtx;
	//Locks the mutex so other threads can't access the below code
	mtx.lock();
	//the critical section that is being controlled by mtx
	mtx.unlock();
	//unlocks the mutex so other threads can access the above code

	//The below show how to use try_lock()
		//try_lock returns true if it locked the mutex and false if it didn't
	if(mtx.try_lock() == true)
		mtx.unlock();

	//That is really all there is to std::mutex
#pragma endregion

#pragma region Recursive_Mutex
	//Essentially a mutex that can be locked any number of times by the same thread
		//unlock must be called that many times too
		//can only be unlocked by owned thread
	std::recursive_mutex rm;
	//Has the same functions as std::mutex
	
	//Examples:
	std::thread t1(func, 8);
	t1.join();
	printf("\n");

	//This has an example on a use case of a recursive mutex:
		//http://stackoverflow.com/questions/2415082/when-to-use-recursive-mutex
#pragma endregion

#pragma region Timed_Mutex
	//A mutex that also supports timed try_lock() functions
	std::timed_mutex tm;

	//Has the same functions as std::mutex with 2 new functions
	//tm.try_lock_for();
	//tm.try_lock_until();

	//Example:
	tm.lock();
	//the below will try to obtain the lock for 3 milliseconds before it gives trying to acquire the lock
		//this is a blocking call meaning the thread will wait until the time runs out or it obtains the lock
		//will return true if it succeeds in locking and false otherwise
		//Used: http://www.cplusplus.com/reference/mutex/timed_mutex/try_lock_for/
	tm.try_lock_for(std::chrono::milliseconds(3));

	//wait until 3 milliseconds from now
		//don't fret too much about all of the std::chrono, for now just realize it is required for .try_lock_until() and .try_lock_for()
	std::chrono::system_clock::time_point sys_clk_tp(std::chrono::system_clock::now() + std::chrono::milliseconds(3));

	//This function takes in the type std::chrono::system_clock::time_point
	tm.try_lock_until(sys_clk_tp);
	//unlock, so the program won't break
	tm.unlock();

#pragma endregion

#pragma region Recursive_Timed_Mutex
	//Defintion
		//A combination of a std::recursive_mutex and a std::timed_mutex
	std::recursive_timed_mutex rtm;

	//has the same functions as std::timed_mutex with the functionality of std::recursive_mutex
	std::thread t2(func2, 8, 2);
	std::thread t3(func2, 8, 3);
	t2.join();
	t3.join();
#pragma endregion
		
#pragma region Shared_Mutex
	//There is also a std::shared_timed_mutex that is a part of C++14
	//There is also potentially going to be a std::shared mutex in C++17

	//For the basics of a shared mutex:
		//http://en.cppreference.com/w/cpp/thread/shared_timed_mutex
#pragma endregion
}


#pragma region Recursive_Mutex_Example
//First lets create another recursive mutex
static std::recursive_mutex rm2;
//int num will be the number of times to lock the the current thread
static void func(int num)
{
	//each time the function is called rm2 will be locked
	rm2.lock();
	//print what number lock this is
	printf("RM Lock Num: %d\n", num);
	//check to break out of the infinite recursion loop
	if (num == 0)
	{
		//unlock now, since this call of the function won't hit the rm2.unlock() at the end
		rm2.unlock();
		//ends the infinite loop
		return;
	}
	//recursively call this function with a num that is one less than the current iteration
	func(--num);
	//unlocks rm2
	//will be called for every call of this function except the one that breaks the recursion loop
	rm2.unlock();
}
#pragma endregion

#pragma region Recursive_Timed_Mutex_Example
//First lets create another recursive_timed_mutex
static std::recursive_timed_mutex rtm2;

//These 2 vectors are used to store the number of times that true was returned from std::recursive_timed_mutex.try_lock_for() or std::recursive_timed_mutex.try_lock_until()
std::vector<bool> v1 = std::vector<bool>();
std::vector<bool> v2 = std::vector<bool>();

//Overall this function will be used for two seperate threads
//The first thread will lock 8 times and the second thread will do different things based on the usage of rtm2
	//if rtm2.lock() is used, then the function will just not lock rtm2 that time
	//int num will be the number of times to lock the the current thread
	//int threadNum is the threads number of id that I give it
static void func2(int num, int threadNum)
{
	//each time the function is called rtm2 will try to lock

	//Can Use:
		//The below tries to lock rtm2 for 1 second and if it fails The function will just continue
	if (threadNum == 3)
		v1.push_back(rtm2.try_lock_for(std::chrono::seconds(1)));	//trys to lock it for 1 second and then will give up trying to lock rtm2
	else
		v2.push_back(rtm2.try_lock_for(std::chrono::seconds(1)));

	//Or:
	//does the same as above - uncomment and see
	/*std::chrono::system_clock::time_point sys_clk_tp(std::chrono::system_clock::now() + std::chrono::seconds(1));
	if (threadNum == 3)
		v1.push_back(rtm2.try_lock_until(sys_clk_tp));	//trys to lock it for 3 milliseconds and then will give up trying to lock rtm2
	else
		v2.push_back(rtm2.try_lock_until(sys_clk_tp));*/

	//print what number lock this is
	printf("RTM %d Lock Num: %d\n", threadNum, num);

	//check to break out of the infinite recursion loop
	if (num == 0)
	{
		//wait a bit to show the try_lock_for() function
		for (int i = 0; i < 1000000000; i++){}

		//While the below is an ugly and naive implementation it makes sure the program runs as intended
		//The below literally just runs through all of the vector and unlocks as many times as needs be
			//makes sure everything is unlocked before the thread finishes
		if (threadNum == 3)
		{
			for (int i = 0; i < v1.size(); i++)
			{
				if (v1[i] == true)
				{
					rtm2.unlock();
				}
			}
		}
		else
		{
			for (int i = 0; i < v2.size(); i++)
			{
				if (v2[i] == true)
				{
					rtm2.unlock();
				}
			}
		}

		//ends the infinite recursion loop
		return;
	}

	//recursively call this function with a num that is one less than the current iteration
	func2(--num, threadNum);
}

//std::recursive_timed_mutex has .lock() as a member function, and it works exactly like it does in std::recursive_mutex
	//didn't use it to show off std::recursive_timed_mutex's
	//Also, using it in the above example creates an infinite loop
#pragma endregion

