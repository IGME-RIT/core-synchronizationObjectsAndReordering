#include "ClassDeclarations.h"

//Event Objects are //??

//For this tutorial we will use the the Windows specific version from the Win 32 library

//The Below is From: https://msdn.microsoft.com/en-us/library/windows/desktop/ms682655(v=vs.85).aspx
//In this there are 2 types of Event Objects
	//Manual-Reset Event Objects
		//An event object whose state remains signaled until it is explicitly reset to nonsignaled by the ResetEvent function.
		//While it is signaled, any number of waiting threads, or threads that subsequently specify the same event object in one of the wait functions, can be released.
	//Auto-Reset Event Objects
		//An event object whose state remains signaled until a single waiting thread is released, at which time the system automatically sets the state to nonsignaled.
			//If no threads are waiting, the event object's state remains signaled.
		//If more than one thread is waiting, a waiting thread is selected.
			//can't assume FIFO ordering
			//External events can change the wait order