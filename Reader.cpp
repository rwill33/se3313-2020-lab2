#include <iostream>
#include <unistd.h>
#include "SharedObject.h"


struct MyShared{

private:
    int threadId;
    int reportId;
    int time;

public:
MyShared(int tId, int rId, int tm)
{
    threadId = tId;
    reportId = rId;
    time = tm;
}    
    
};

int main(void)
{
	std::cout << "I am a reader" << std::endl;
	while(true){
		Shared<MyShared> shared("sharedMemory"); //This is the owner of sharedMamory
		std::cout << shared << std::endl;
		std::cout << "Reader Thread: " << std::endl;
		sleep(2);
	}
}
