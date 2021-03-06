// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#define APPWM_ICONNOTIFY (WM_APP + 1)
#include "stdafx.h"
#include <shlwapi.h>
#include<Windows.h>
#include<windows.h>
#include<WinBase.h>
#include<Shlobj.h>
#include <Shldisp.h>




void showTaskBar(bool show)
{
	HWND taskbar = FindWindow(_T("Shell_TrayWnd"), NULL);
	HWND start = FindWindow(_T("Button"), NULL);

	if (taskbar != NULL) {
		ShowWindow(taskbar, show ? SW_SHOW : SW_HIDE);
		UpdateWindow(taskbar);
	}
	if (start != NULL) {
		// Vista
		ShowWindow(start, show ? SW_SHOW : SW_HIDE);
		UpdateWindow(start);
	}
}
void toggleDesktop() 
{
	CoInitialize(NULL);
	IShellDispatch4 *pShellDisp = NULL;
	HRESULT sc = CoCreateInstance(CLSID_Shell, NULL, CLSCTX_SERVER, IID_IDispatch, (LPVOID *)&pShellDisp);
	sc = pShellDisp->ToggleDesktop();
}
void showIcons(BOOL show)
{
	HWND hProgman = FindWindowW(L"Progman", L"Program Manager");
	HWND hChild = GetWindow(hProgman, GW_CHILD);
	if (!(show)) 
	{
		ShowWindow(hChild, SW_HIDE);
	} 
	else {
		ShowWindow(hChild, SW_SHOW);
	}
	
}
void hide()
{
	showIcons(false);
	toggleDesktop();
	showTaskBar(false);
}
void show()
{
	showIcons(true);
	toggleDesktop();
	showTaskBar(true);
}
int main()
{
	hide();
	while (!(GetAsyncKeyState(VK_SPACE) & 0x80000000))
	{
		Sleep(100);
	}
	show();
	Sleep(25);
	showIcons(true);
}

