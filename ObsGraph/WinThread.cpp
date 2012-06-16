#include <process.h>
#include "WinThread.h"

WinThread::WinThread() {}

void WinThread::Start(void * arg)
{
   setArg(arg); // store user data
   setTerminated(false);
   hThread = (HANDLE)_beginthreadex(NULL,         // security
                                   0,            // stack size
                                   WinThread::EntryPoint,  // entry-point-function
                                   this,           // arg list holding the "this" pointer
								   0,  // Create running, not suspended
                                   &threadID );
}

void WinThread::Run(void * arg)
{
	Setup();
	Execute(arg);
}

/*static */
unsigned __stdcall WinThread::EntryPoint(void* pthis)
{
   WinThread * pt = (WinThread*)pthis;
   pt->Run(pt->getArg());

   return 1;
}

void WinThread::Setup() { }
void WinThread::Execute(void *) { }
