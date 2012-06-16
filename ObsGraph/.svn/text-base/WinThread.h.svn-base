#ifndef WINTHREAD_H
#define WINTHREAD_H

#include <windows.h>

class WinThread
{
	public:
		WinThread();
		void Start(void * arg);

		HANDLE getHandle() {return hThread;}
		unsigned int getThreadID() {return threadID;}
		void * getArg() const {return Arg;}
		void setArg(void* a){Arg = a;}
		bool isTerminated() {return terminated;}
		void setTerminated(bool val) {terminated = val;}
	protected: 
		void Run(void * arg);
		static unsigned __stdcall EntryPoint(void*);
		virtual void Setup();
		virtual void Execute(void*);


		bool terminated;
	private:
		HANDLE hThread;
		unsigned int threadID;
		void * Arg;

};

#endif