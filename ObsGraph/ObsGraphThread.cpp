#include "ObsGraphThread.h"
#include "Patcher.h"
#include "BWAddresses.h"
#include "BWUtil.h"
#include "Window.h"

Window * myWindow;
WNDPROC OldWndProc;

void TempDrawHook() {
	// FIXME: get rid of this function and move hooks to another file
	//BWDrawTransparentBox(20,20,40,40,188);
	/*DWORD oldFormat = *(DWORD *)CUR_TEXT_FORMAT;
	BWFormatTextR(BWTF_NORMAL);
	BWDrawText(20,20, "Oh hi there");
	BWRestoreTextFormat(oldFormat);*/
	myWindow->draw(0, 0);	
}

LRESULT CALLBACK TempWndProcHook(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// FIXME: move hooks into another file
	bool bHandled = false;
	
	//TODO: devise a way to handle dragging vs. clicking
	//		Perhaps you should use some sort of stack
	//		BUTTONDOWN = push
	//		MOUSEMOVE  = push (call startdrag or updatedrag if mousemove is already on stack)
	//		BUTTONUP   = pop (until corresponding buttondown is popped off)
	//		Would obviously need a stack per component with this method
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	
	POINTS mousePt;
	switch(uMsg) {
		// for now just assume everything's a drag
		case WM_LBUTTONDOWN:
			mousePt = MAKEPOINTS(lParam);
			mousePt.x -= (SHORT)clientRect.left;
			mousePt.y -= (SHORT)clientRect.top;
			if(myWindow->hitTest(mousePt.x, mousePt.y)) {
				myWindow->startDrag(mousePt.x, mousePt.y);
				bHandled = true; // either disable this functionality when dialogs are up or draw over them
			}
			break;
		case WM_MOUSEMOVE:
			mousePt = MAKEPOINTS(lParam);
			mousePt.x -= (SHORT)clientRect.left;
			mousePt.y -= (SHORT)clientRect.top;
			// this should really be finding a window which has a "drag stack" before calling this function
			myWindow->updateDrag(mousePt.x, mousePt.y);
			break;
		case WM_LBUTTONUP:
			mousePt = MAKEPOINTS(lParam);
			mousePt.x -= (SHORT)clientRect.left;
			mousePt.y -= (SHORT)clientRect.top;
			myWindow->endDrag(mousePt.x, mousePt.y);
			break;
		
		case WM_KEYDOWN:
			// normally we'd check for which window is focused here, but we're too cool for that atm
			myWindow->receivedKey(wParam);
			break;
			
		case WM_LBUTTONDBLCLK:
			mousePt = MAKEPOINTS(lParam);
			mousePt.x -= (SHORT)clientRect.left;
			mousePt.y -= (SHORT)clientRect.top;
			if(myWindow->hitTest(mousePt.x, mousePt.y)) {
				myWindow->receivedLeftDblClick(mousePt.x, mousePt.y);
				bHandled = true; // either disable this functionality when dialogs are up or draw over them
			}
			break;
		case WM_RBUTTONDBLCLK:
			mousePt = MAKEPOINTS(lParam);
			mousePt.x -= (SHORT)clientRect.left;
			mousePt.y -= (SHORT)clientRect.top;
			if(myWindow->hitTest(mousePt.x, mousePt.y)) {
				myWindow->receivedRightDblClick(mousePt.x, mousePt.y);
				bHandled = true; // either disable this functionality when dialogs are up or draw over them
			}
			break;
		case WM_MBUTTONDBLCLK:
			mousePt = MAKEPOINTS(lParam);
			mousePt.x -= (SHORT)clientRect.left;
			mousePt.y -= (SHORT)clientRect.top;
			if(myWindow->hitTest(mousePt.x, mousePt.y)) {
				myWindow->receivedMiddleDblClick(mousePt.x, mousePt.y);
				bHandled = true; // either disable this functionality when dialogs are up or draw over them
			}
			break;
	}
	
	if(!bHandled)
		return CallWindowProc(OldWndProc, hwnd, uMsg, wParam, lParam);
	else
		return 0;
}

ObsGraphThread::ObsGraphThread() {}

/*
constructor TStartrisThread.Create(CreateSuspended: Boolean);
begin
  inherited Create(CreateSuspended);
  AllocConsole;

  SCWnd := FindWindow(nil,'Brood War');

  WriteLn('Loading Fonts...');
  LoadFont('ObsImages\8x12font.jpg',8,12,0);
  WriteLn('Fonts loaded.');

  WriteLn('Creating Hotkey Thread...');
  FHotkeyThread := THotkeysThread.Create(True);
  FHotkeyThread.OnHotkey := HotkeyEvent;
  FHotkeyThread.AddKey(VK_F6,2);
  FHotkeyThread.AddKey(VK_F7,2);
  FHotkeyThread.AddKey(VK_F8,2);
  FHotkeyThread.AddKey(Ord('I'));
  FHotkeyThread.AddKey(Ord('J'));
  FHotkeyThread.AddKey(Ord('K'));
  FHotkeyThread.AddKey(Ord('L'));
  FHotkeyThread.AddKey(VK_F5,2);

  WriteLn('Hotkey thread initialized.');
  SndNum := 1;

  // Add patches
  AddPatch(Offsets.HOOK_Draw,Cardinal(@DrawHook));
  AddPatchedMem(Offsets.PTCH_TextRefresh1,[$90,$90]);
  AddPatchedMem(Offsets.PTCH_TextRefresh2,[$EB,$04]);

  // Create our game window
  GameWindow := TGameWindow.Create(200,34,GAME_WIDTH,GAME_HEIGHT,
                                  'Startris: Brood Blox',0,True,True);
  TestBlock := TTestBlock.Create;
  TestBlock.XPos := 0;
  TestBlock.YPos := 0;
  TestBlock.XVel := 1;
  TestBlock.YVel := 1;
  GameWindow.AddChild(TestBlock);
  //GameWindow := TGameWindow.Create(200,34,50,50,'Game Window!',0,True,True);
end;
*/
void ObsGraphThread::Setup()
{
	patcher = new Patcher();
	
	patcher->AddPatch(HOOK_DRAW, (DWORD)&TempDrawHook);
	const unsigned short refreshMem1 = 0x9090;
	const unsigned short refreshMem2 = 0x04EB;
	patcher->AddPatchedMem(PTCH_TEXTREFRESH1, (byte*)&refreshMem1, 2);
	patcher->AddPatchedMem(PTCH_TEXTREFRESH2, (byte*)&refreshMem2, 2);
	
	myWindow = new Window("Cool Window, Bro", 20, 20, 220, 220);
}

/*
procedure TStartrisThread.Execute;
begin
  FHotkeyThread.Resume;
  HijackWndProc;

  while not Terminated do
  begin
    if (IsInGame) and (not Patched) then
    begin
      Patch;
    end
    else if (not IsInGame) and (Patched) then
      Unpatch;

    if IsInGame then
    begin
      UpdateLoop;
      Sleep(TICK_TIME);
    end
    else
      Sleep(100);
  end;

  FreeConsole;
  Images.Free;
  UnHijackWndProc;
  if Terminated then
    exit;
end;
*/
void ObsGraphThread::Execute(void* arg)//FIXME: Write This
{
	bool ingame = false;
	while(!isTerminated()) {
		if(!ingame && IsInGame()) {
			ingame = true;
			HWND SCWnd = FindWindow(NULL,"Brood War");
			OldWndProc = (WNDPROC)SetWindowLong(SCWnd, GWL_WNDPROC, (LONG)TempWndProcHook);
			patcher->Patch();
			BWPlaySound(0x046D); // This is not warcraft in space!
			Sleep(3300);
			BWPlaySound(0x046E); // Its much more sophisticated!
			Sleep(2700);
			BWPlaySound(0x046F); // I know its not 3D!
		}
		else if(ingame && !IsInGame()) {
			ingame = false;
			patcher->Unpatch();
			HWND SCWnd = FindWindow(NULL,"Brood War");
			SetWindowLong(SCWnd, GWL_WNDPROC, (LONG)OldWndProc);
		}
		
		Sleep(150);
	}
	
	delete patcher;
}