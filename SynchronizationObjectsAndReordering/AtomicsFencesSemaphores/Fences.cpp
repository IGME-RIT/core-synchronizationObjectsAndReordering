#include "ClassDeclarations.h"
#include <atomic>

//Used:
	//http://preshing.com/20120913/acquire-and-release-semantics/
	//http://preshing.com/20120710/memory-barriers-are-like-source-control-operations/
	//http://stackoverflow.com/questions/14581090/how-to-correctly-use-stdatomic-signal-fence

//A Fence or more Commonly called  Memory Barrier
	//It is a hardware operation that ensures the ordering of different reads and writes
	//This can also be talked about under the name Acquire Release Semantics

//Several Versions of Fences - Used: http://preshing.com/20120710/memory-barriers-are-like-source-control-operations/ for part of the list
	//MemoryBarrier; // - Windows.h
	//__asm volatile ("" : : : "memory") // - Inline Assembly
		//Power PC version: __asm volatile ("lwsync" : : : "memory")
	//_ReadWriteBarrier; // - intrin.h
	//atomic_thread_fence();
		//A portable version of fences included in the std library
	//atomic_signal_fence() <- only performs synchronizations between a signal handler and other code running on the same thread
		//does not synchronize code between threads
		//compiler optimizations and reorderings of loads and stores are inhibited in the same way as with atomic_thread_fence
		//hardware fence instructions that atomic_thread_fence would have inserted aren't emitted
		//can be used to specify the order in which actions performed by the thread become visible to the signal handler
		//http://stackoverflow.com/questions/14581090/how-to-correctly-use-stdatomic-signal-fence
	//Many C++11 Atomic Object Operations
		//std::atomic<>::load(std::memory_order_acquire) <- the atomic object's load function can be given a memory order that acts as a memory barrier
	//Any Win32 Interlocked operation
		//Interlocked API - https://msdn.microsoft.com/en-us/library/windows/desktop/ms684122.aspx

//In this tutorial we will focus on atomic_thread_fence() and how to use it
	//This is due to its portable nature and the fact that it is a memory fence itself

//Before we start it is important to mention that standard library atomic objects' member functions allow for specifying memory ordering
	//This means that they don't need fences as they handle their own memory ordering, since 

//Before you continue, some definitions:
	//register - a piece of hardware for a CPU core to store small amounts of data for quick access
	// the mov assembly instruction - mov A, B
		//moves B into A
			//Example: move [X], 1
				//move 1 into [X] <- storing 1 into the variable [X]
			//Example: move r1, [Y]
				//move [Y] into the register r1 <- loading the variable [Y] into a register to use it immediately

//Now to describe the different types of memory barriers, Please read:
	//http://preshing.com/20120710/memory-barriers-are-like-source-control-operations/

//Do not continue until you have read the above link

//Now that you have a basic idea of the types of generic memory barriers, we will focus of C++11's atomic_thread_fence()
//This is a portable memory barrier that is minimally extracted from the hardware, but is still very efficient
//We are focusing on this due to its portability

//Below are examples of the C++11 release fence and acquire fence
	//std::atomic_thread_fence(std::memory_order_acquire);
	//std::atomic_thread_fence(std::memory_order_release);

//A few things thing to understand before going on:
	//std::memory_order_relaxed, means that the object that has this memory order doesn't care if memory reordering happens
//std::atomic<>.load() does nothing more than get the variable's value and std::atomic<>.store() does nothing more than save that value into the variable
	//These operations are atomic
//std::atomic_thread_fence() will require a C++11 Atomic Object

//Read the below on a tutorial on fences
	//http://preshing.com/20130922/acquire-and-release-fences/

//This should give you a basic understanding of memory barriers
//We will use these in the Lockless Multithreading Tutorial