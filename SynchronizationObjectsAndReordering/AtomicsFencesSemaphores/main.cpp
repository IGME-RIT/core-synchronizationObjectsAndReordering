/*
Synchronization Objects and Memory Reordering
(c) 2016
original authors: Sean Connolly
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*	This tutorial deals with the various forms of synchronization objects and the concept of memory reordering.
*	It covers synchronization objects such as Fences, Locks, Mutexes, Semaphores, Atomics very briefly, and Event Objects.
*/

#include "ClassDeclarations.h"

int main()
{
	//Go to the individual CPP files for the tutorials

	//Start with Reordering.cpp
	//Then go to Fences.cpp
	//After that you can go to Semaphores.cpp or Atomics.cpp in either order

	//Done with Atomics
	Atomics atomics;
	//atomics.basics();

	/*Fences fences;
	fences.basicFenceExample();*/

	Mutexes mtxs;
	//mtxs.mutexExamples();

	Locks locks;
	locks.lockExamples();
	
	getchar();
	return 0;
}