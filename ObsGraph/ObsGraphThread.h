#ifndef OBSGRAPHTHREAD_H
#define OBSGRAPHTHREAD_H

#include "WinThread.h"
#include "Patcher.h"

/*
type
  TStartrisThread = class(TThread)
  private
    FHotkeyThread: THotkeysThread;
    procedure HotkeyEvent(Key: Integer);
  protected
    procedure Execute; override;
  public
    constructor Create(CreateSuspended: Boolean);
  end;
*/

class ObsGraphThread: public WinThread
{
	public:
		Patcher* patcher;
		ObsGraphThread();
	protected:
		void Setup();
		void Execute(void*);
};

#endif