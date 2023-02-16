#include <iostream>
#include "thread.h"
#include "SharedObject.h"
#include "Semaphore.h"
#include <thread>
#include <stack>
#include <unistd.h>
#include <time.h>

using namespace std;

struct MyShared{
    int thId;
    int repId;
    int tDelay;
    int tElap;
    
};

	Semaphore rSem("reader", 1, true);
	Semaphore wSem("writer", 1, true);

class WriterThread : public Thread{
	public:
		int threadNum;
		bool flag = false;
		int delay;
		int reportId;
		//MyShared share;
		
		
		WriterThread(int delay, int tCount):Thread(8*1000){
			this-> threadNum = tCount; 
			this -> delay = delay;
			this -> reportId = 0;

		}

		virtual long ThreadMain(void) override{
		
			//declare shared memory var so this thread can access it
			Shared<MyShared> sharedMemory ("sharedMemory");
			while(true)
			{
				time_t first = time(0);
				wSem.Wait();
				sleep(delay);
				time_t last = time(0);
				sharedMemory->thId = threadNum;
				sharedMemory->repId = reportId++;
				sharedMemory->tDelay = delay;
				sharedMemory->tElap = (last-first);
				wSem.Signal();
				rSem.Signal();
				
				if(flag == true)
				{
				    break;
				}
			}
	        return 1;	
		}
};

int main(void)
{
	
	Shared<MyShared> shared("sharedMemory", true);
	cout << "I am a Writer" << endl;
	string nThread = "";
	int delay = 0;
	WriterThread* th;
	stack<WriterThread*> tStack;
	int tCount = 0;
	while(true)
	{
	    tCount++;
	    cout << "\nWould you like to create a new thread (y/n)?\n";
	    cin >> nThread;
	    if(nThread == "n")
	    {
	        break;
	    }
	    cout << "\nWhat is the Time delay for this Thread in s?\n";
	    cin >> delay;
	    th = new WriterThread(delay, tCount);
	    tStack.push(th);
	}
	while(!tStack.empty())
	{
	    th = tStack.top();
	    th->flag = true;
	    delete th;
	    tStack.pop();
	}

}


