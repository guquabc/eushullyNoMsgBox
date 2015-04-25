#include <windows.h>
#include "detours.h"


static int (WINAPI * TrueMessageBoxA)(HWND hWnd,LPCSTR lpText,LPCSTR lpCaption,UINT uType)=MessageBoxA;


int WINAPI  MyMessageBoxA(HWND hWnd,char* lpText,char* lpCaption,UINT uType)
{
	return IDYES;
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
    LONG error;
    (void)hinst;
    (void)reserved;

    if (DetourIsHelperProcess()) {
        return TRUE;
    }

    if (dwReason == DLL_PROCESS_ATTACH) {
        DetourRestoreAfterWith();

		LoadLibrary("user32.dll");
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
		
		DetourAttach(&(PVOID&)TrueMessageBoxA, MyMessageBoxA);
        error = DetourTransactionCommit();

    }
    else if (dwReason == DLL_PROCESS_DETACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
		
		DetourDetach(&(PVOID&)TrueMessageBoxA, MyMessageBoxA);
        error = DetourTransactionCommit();

    }
    return TRUE;
}

//
///////////////////////////////////////////////////////////////// End of File.
