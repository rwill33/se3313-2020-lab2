#include <iostream>
#include <unistd.h>
#include "SharedObject.h"
#include "Semaphore.h"


struct MyShared{
    int thId;
    int repId;
    int tDelay;
    int tElap;
};   
    

int main(void)
{
	std::cout << "I am a reader" << std::endl;

	Semaphore wSem("writer", 1, false);
	Semaphore rSem("reader", 1, false);


	Shared<MyShared> shared("sharedMemory"); //This is the owner of sharedMamory
	while(true){
		rSem.Wait();
		wSem.Wait();

		std::cout << "Thread Id: " << shared->thId << "Report Id:" << shared->repId << "Time Elapsed" << shared->tElap << "Delay Time:" << shared->tDelay << std::endl;
		wSem.Signal();
	}
}
