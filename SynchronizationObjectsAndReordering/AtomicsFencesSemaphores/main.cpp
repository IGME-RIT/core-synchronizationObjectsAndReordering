#include "ClassDeclarations.h"

int main()
{
	//Go to the individual CPP files for the tutorials

	//Start with Reordering.cpp
	//Then go to Fences.cpp
	//After that you can go to Semaphores.cpp or Atomics.cpp in either order

	//Done with Atomics
	Atomics atomics;
	atomics.basics();

	/*Fences fences;
	fences.basicFenceExample();*/

	//The above are all you need in order to continue onto the lockless programming tutorial

	getchar();
	return 0;
}