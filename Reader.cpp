#include <iostream>
#include <unistd.h>
#include <SharedObject.h>


struct MyShared{
	int ;
};

int main(void)
{
	std::cout << "I am a reader" << std::endl;
	while(true){
		Shared<MyShared> shared("sharedMemory"); //This is the owner of sharedMamory
		shared.get();
		std::cout << "Reader Thread: " << std::endl;
		sleep(2);
	}
}
