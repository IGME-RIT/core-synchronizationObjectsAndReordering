#include "ClassDeclarations.h"

//What is a read and what is a write
//Read
	//if(player){} <- reads/loads player and checks if player is not NULL
//Write
	//player = Player(); <- writes/stores the newly created Player into player

//What is Memory Reordering?
	//Lets start with some code:
		/*
		int num1 = 1;

		//1 read/load
		int temp1 = num1 + 1;

		//1 write/store
		num1 = 3;
		*/
	//This is just some code with reads and writes

	//What could happen to this due to the CPU or the compiler optimizing:
	/*
	it will load in num1
	then it will store 3 in num1
	then temp gets the number 2 (the loaded value of num1 + 1)
	*/

	//In a singly threaded system this is fine and not an issue as the output is still the same
	//This can cause issues in a multithreaded system
	//Reordering can either happen at compile time, due to the compiler, or at run time, due to the CPU

	//The Below is an example of some code that code have issues in a multithreaded environment
	//Example:
		/*
		int Value;
		int IsPublished = 0;
		 
		void sendValue(int x)
		{
		    Value = x;
		    IsPublished = 1;
		}
		*/
		//If this code was being used in a multithreaded system,
			//what would happen if the compiler reordered the store to IsPublished before the store to Value
			//This could mean another thread could come along and see that IsPublished is true and access value, before the store to value happens
				//obviously this can cause issues
		//Example taken verbatim from: http://preshing.com/20120625/memory-ordering-at-compile-time/

	//When the compiler reorders memory it follows one rule:
		//Thou shalt not modify the behavior of a single-threaded program.
			//This means that in single-threaded programs you will most likely never notice the reordering without the Assembly
			//Mutexes and semaphores are designed to prevent memory ordering around their call sites
		//The above is slightly paraphrased from: http://preshing.com/20120625/memory-ordering-at-compile-time/
	//CPU reordering
		//Invisible in single-thread programs
		//The effects are only visible in multicore and multiprocessor systems

//To prevent memory reordering there are fences or memory barriers
	//So, a good idea for the next tutorial to read is the Fences.cpp file

//The above gives you a basic understanding of memory reordering without going too deep into the assembly or anything like that
//To learn more:
	//http://preshing.com/20120625/memory-ordering-at-compile-time/
	//http://preshing.com/20120515/memory-reordering-caught-in-the-act/
		//The person that writes this blog was a Technical Architect at Ubisoft Montreal and his blog is really good