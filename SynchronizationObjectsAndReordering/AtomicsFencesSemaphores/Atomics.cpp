#include "ClassDeclarations.h"
#include <atomic>


//Will be a very brief preview of the atomic library, will go into more depth in the Lockless Programming Tutorial
	//This is because they are very intertwined

//The main characteristic of atomic objects is that access to this contained value from different threads cannot cause data races.
	//Taken from: http://www.cplusplus.com/reference/atomic/atomic/

//This will just show syntax and how to access the value of the variable

//almost like there are two libraries in one
	//first is sequentially consistent atomics - assumes memory_order_seq_cst (sequentially consistent)
		//The default memory ordering for all functions of std::atomic have a default value of memory_order_seq_cst
	//second are low level atomics - these allow for certain memory orders to be passed in the form of enums
		//example std::atomi<int> p; p.store(1, std::memory_order_release);
		//This is rather advanced and will be covered later
	//https://www.youtube.com/watch?v=X1T3IQ4N-3g - 33:37 about

struct num
{
	int number;
};

void Atomics::basics()
{
	//Syntax:
	std::atomic<int> counter1;

	//Can treat it almost like an int at this point

	//How to save to it
	counter1 = 3;

	//How to read from it
	int temp1 = counter1;

	//To show that temp got the right value
	printf("Temp1: %d\n", temp1);
	//To show how to read from it again and to show that we saved the correct value to it
	std::cout << "Counter1: " << counter1 << std::endl;

	//To increment
	counter1++;
	//same with decrement

	//Notice how for a basic integer type the atomic object overloads the increment and decrement operators
	//This shows how atomic overloads for use with basic types
		//Remember this does not include strings or arrays

	//Also have typedefs of atomic objects of basic data types
		//Example: std::atomic_char p;
			//Equivalent to: std::atomic<char> p;
		///A full list of them: http://en.cppreference.com/w/cpp/atomic/atomic


	//Non-Basic Variable Types

	std::atomic<num> counter2;

	//Unlike basic data types atomics can't overload the operators of non-basic data types
	//For this example lets use a struct

	//We have to treat it slightly differently than a struct

	//How to save to it
		
	//Can use the aggregate constructor just like any struct
	counter2 = { 3 };
	//Or to save to the individual members of the struct you need to access to the struct's data
		//do this with _My_val
	counter2._My_val.number = 3;

	//How to read from it
	int temp2 = counter2._My_val.number;

	//To show that you got the right value
	printf("Temp2: %d\n", temp2);
	//To show that you are accessing the right value
	std::cout << "Counter2: " << counter2._My_val.number << std::endl;

	//This is enough for the basic use of atomics
	//They are much more powerful than this, which will be shown off in the lockless programming tutorial
}
