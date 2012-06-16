/*
exports
  //BWL Version 4
  GetPluginAPI,
  GetData,
  OpenConfig,
  ApplyPatchSuspended,
  ApplyPatch,
  //My Functions
  DllMain;
*/

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "ObsGraphThread.h"

/*
STARCRAFTBUILD: Integer = 13;
  PluginMajor = 0;
  PluginMinor = 1;
  PluginName = 'Startris (1.16.1)';
*/

#define STARCRAFTBUILD 13
#define PLUGINMAJOR 0
#define PLUGINMINOR 1
#define PLUGINNAME "ObsGraph (1.16.1)"

/*
type
  TBWL_ExchangeData=packed record
    PluginAPI:Integer;
    StarCraftBuild:Integer;
    NotSCBWmodule:LongBool;                //Inform user that closing BWL will shut down your plugin
    ConfigDialog:LongBool;                 //Is Configurable
  end;
*/
typedef struct
{
	int PluginAPI;
	int StarCraftBuild;
	bool NotSCBWmodule;
	bool ConfigDialog;
} BWL_ExchangeData;

HINSTANCE hInstance;

/*
procedure OnInjection; // called only when we're injected into starcraft.exe
var
  StartrisThread: TStartrisThread;
begin
  StartrisThread := TStartrisThread.Create(True);
  StartrisThread.Resume;
end;
*/

void OnInjection()
{
	ObsGraphThread * thread = new ObsGraphThread();
	thread->Start(NULL);
}

/*
procedure DllMain(reason: integer); // called every time the dll is loaded/unloaded
var
  buf : array[0..MAX_PATH] of char;
  loader : string;
begin
    case reason of
      DLL_PROCESS_ATTACH:
      begin
        GetModuleFileName(0, buf, SizeOf(buf));
        loader := buf;
        loader := ExtractFileName(loader);
        if Pos('starcraft', LowerCase(loader)) > 0 then
          OnInjection;
      end;
   end;
end;
*/

BOOL WINAPI DllMain(HMODULE hModule, DWORD  reason, LPVOID lpReserved)
{
	char buf[MAX_PATH];

	if(reason == DLL_PROCESS_ATTACH)
	{
		hInstance = hModule;
		GetModuleFileName(0, buf, MAX_PATH);
		if(strstr(buf, "Chaoslauncher.exe") == NULL)
			OnInjection();
	}

	return true;
}

/*
function GetDescription:String;
begin
  Result := 'Startris: Brood Blox v'+IntToStr(PluginMajor)+'.'+IntToStr(PluginMinor)+#13#10+
                'The Overmind has infested colored blocks around the globe! Are you a bad enough dude to stack them into lines?'#13#10+
                'by tec27';
end;
*/

char* GetDescription()
{
	char* result;
	result = (char*)malloc(1024);
	sprintf(result, "ObsGraph v%d.%d\r\nAn extensible utility plugin for displaying data and graphs inside StarCraft.\r\nby tec27", PLUGINMAJOR, PLUGINMINOR);
	return result;
}


/*
procedure GetPluginAPI(var Data:TBWL_Exchangedata);cdecl;
begin
  //BWL Gets version from Resource - VersionInfo
  Data.PluginAPI := 4; //BWL 4
  Data.StarCraftBuild := STARCRAFTBUILD;
  Data.ConfigDialog := True; // We display a config dialog
  Data.NotSCBWmodule := True; // No warning message
end;
*/

extern "C" __declspec(dllexport) void GetPluginAPI(BWL_ExchangeData &Data)
{
	Data.PluginAPI = 4;
	Data.StarCraftBuild = STARCRAFTBUILD;
	Data.ConfigDialog = true;
	Data.NotSCBWmodule = true;
}

/*
procedure GetData(Name,Description,UpdateUrl:Pchar);cdecl;
begin
  //if necessary you can add Initialize function here
  //possibly check CurrentCulture (CultureInfo) to localize your DLL due to system settings
  StrPCopy(name, PluginName);
  StrPCopy(description, GetDescription);
  StrPCopy(updateurl, 'http://rockify.net/Startris/');
end;
*/

extern "C" __declspec(dllexport) void GetData(char* Name, char* Description, char* UpdateUrl)
{
	strcpy(Name, PLUGINNAME);
	strcpy(Description, GetDescription());
	strcpy(UpdateUrl, "http://rockify.net/ObsGraph/");
}

/*
function OpenConfig():BOOL;cdecl;
{var
  ConfigForm: TConfigDialog;}
begin
  //If you set "Data.bConfigDialog = true;" at function GetPluginAPI then
  //BWLauncher will call this function if user clicks Config button

  //You'll need to make your own Window here
  // Open the config dialog
  {ConfigForm:=TConfigDialog.Create(nil);
  try
    ConfigForm.ShowModal;
  finally
    ConfigForm.Free;
  end;}
  Result := True;
end;
*/

extern "C" __declspec(dllexport) bool OpenConfig()
{
	//FIXME: implement ConfigDialog class
	return true;
}

/*
function ApplyPatchSuspended(hProcess:THandle;ProcessID:Cardinal):BOOL;cdecl;
begin
  //This function is called on suspended process
  //Durning the suspended process some modules of starcraft.exe may not yet exist.
  //the dwProcessID is not checked, its the created pi.dwProcessId

  //here is safe place to call starcraft methods to load your DLL as a module
  //hint - process shoudnt be suspended :)
  //hint - WNDPROCCALL

  //   dummy example
  //patch:array[0..0]of byte = ($90);
  //WriteProcessMemory( hProcess, Pointer($00123456), patch, sizeof(patch), nil);

  Result := True;
  //return false; //something went wrong
end;
*/

extern "C" __declspec(dllexport) bool ApplyPatchSuspended(HANDLE hProcess, unsigned int ProcessID)
{
	return true;
}

/*
function ApplyPatch(hProcess:THandle; ProcessID:Cardinal):BOOL;cdecl;
var
  RemoteStr, LoadLibAddr: Pointer;
  hSCProcess: THandle;
  FullDllName: string;
  hThread: Cardinal;
  buf : array[0..MAX_PATH] of char;
begin
  //This fuction is called after
  //ResumeThread(pi.hThread);
  //WaitForInputIdle(pi.hProcess, INFINITE);
  //EnableDebugPriv() - 
  //   OpenProcessToken...
  //   LookupPrivilegeValue...
  //   AdjustTokenPrivileges...
  //
  //the dwProcessID is checked by GetWindowThreadProcessId
  //so it is definitly the StarCraft

  GetModuleFileName(HInstance, buf, SizeOf(buf));
  FullDllName := buf;

  if not FileExists(FullDllName) then
    MessageBox(0, PChar('Could not find Startris''s BWL file!'), 'Error!', MB_ICONERROR or MB_OK);

  hSCProcess := hProcess;

  // Our CreateRemoteThread Dll Injector :)
  LoadLibAddr := GetProcAddress(GetModuleHandle('kernel32.dll'),'LoadLibraryA');
  RemoteStr := VirtualAllocEx(hSCProcess,nil,StrLen(PChar(FullDllName)),MEM_COMMIT or MEM_RESERVE,PAGE_READWRITE);
  WriteProcessMemory(hSCProcess,RemoteStr,PChar(FullDllName),StrLen(PChar(FullDllName)),Cardinal(nil^));
  hThread := CreateRemoteThread(hSCProcess,nil,0,LoadLibAddr, RemoteStr, 0, Cardinal(nil^));
  if hThread = 0 then
    MessageBox(0,PChar('Remote thread creation failed. Error Code: ' + IntToStr(GetLastError())),'Error!', MB_OK or MB_ICONERROR);

  Result := True; //everything OK
end;
*/

extern "C" __declspec(dllexport) bool ApplyPatch(HANDLE hProcess, unsigned int ProcessID)
{
	char szPath[MAX_PATH];
	GetModuleFileNameA(hInstance, szPath, MAX_PATH);
	
	LPTHREAD_START_ROUTINE loadLibAddress = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("Kernel32"), "LoadLibraryA" );
	if(loadLibAddress == NULL) {
		MessageBox(NULL, "Could not get LoadLibrary address.", "ObsGraph Error", MB_OK);
		return false;
	}

	void* pathAddress = VirtualAllocEx(hProcess, NULL, strlen(szPath) + 1, MEM_COMMIT, PAGE_READWRITE);
	if(pathAddress == NULL) {
		MessageBox(NULL, "Could not allocate memory in the Starcraft Process.", "ObsGraph Error", MB_OK);
		return false;
	}

	SIZE_T bytesWritten;
	BOOL success = WriteProcessMemory(hProcess, pathAddress, szPath, strlen(szPath) + 1, &bytesWritten);
	if(!success || bytesWritten != strlen(szPath) + 1) {
		MessageBox(NULL, "Did not write to Starcraft's memory correctly.", "ObsGraph Error", MB_OK);
		return false;
	}

	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, loadLibAddress, pathAddress, 0, NULL);
	if(hThread == NULL) {
		MessageBox(NULL, "Could not create remote thread.", "ObsGraph Error", MB_OK);
		return false;
	}

	WaitForSingleObject(hThread, INFINITE);

	DWORD hLibModule; // Base address of the loaded module
	GetExitCodeThread(hThread, &hLibModule);
	if(hLibModule == 0) {
		MessageBox(NULL, "Error loading library remotely.", "ObsGraph Error", MB_OK);
		return false;
	}

	VirtualFreeEx(hProcess, pathAddress, strlen(szPath) + 1, MEM_RELEASE);
	CloseHandle(hThread);

	return true;
}