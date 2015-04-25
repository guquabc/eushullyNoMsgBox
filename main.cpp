#include <windows.h>
#include<stdio.h>
#include <conio.h>
#include "detours.h"
int main()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD dwFlags = CREATE_DEFAULT_ERROR_MODE | CREATE_SUSPENDED;
	memset(&si,0,sizeof(STARTUPINFO));
	memset(&pi,0,sizeof(PROCESS_INFORMATION));
	si.cb=sizeof(STARTUPINFO);
	if(DetourCreateProcessWithDllEx(
		"AGE.EXE",   // No module name (use command line)
		0,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi ,				// Pointer to PROCESS_INFORMATION structure
		"hookMsgbox32.dll",
		NULL))
	{
		printf("成功\n");
	} 
	else
	{
		printf("失败\n");
		DWORD dwError = GetLastError();
		printf("%d",dwError);
	}
	printf("按任意键退出");
	getch();
	return 0;
}