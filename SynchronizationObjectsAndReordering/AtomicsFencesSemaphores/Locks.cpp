#include "ClassDeclarations.h"

static void fun()
{
	std::lock_guard<std::mutex> lck1();
	std::unique_lock<std::mutex> lck2();
	//std::shared_lock<std::mutex> lck3(); //Also a type of lock in C++14
		//Uses: #include <shared_mutex>
}