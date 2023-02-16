#include <iostream>
#include <unistd.h>
#include "SharedObject.h"


struct MyShared{
    int thId;
    int repId;
    int tDelay;
    int tElap;
    
};   
    

int main(void)
{
	std::cout << "I am a reader" << std::endl;
	Shared<MyShared> shared("sharedMemory"); //This is the owner of sharedMamory
	while(true){
		
		std::cout << "Thread Id: " << shared->thId << "Report Id:" << shared->repId << "Time Elapsed" << shared->tElap << "Delay Time:" << shared->tDelay << std::endl;
		sleep(2);
	}
}
