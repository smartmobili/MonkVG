#pragma once

#include <Windows.h>

class CxWindow
{
public:
	CxWindow(HINSTANCE instance);
	virtual ~CxWindow();

	bool initializeWindow();   
	static LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);
	WPARAM run();

private:
	HINSTANCE _hInstance;
	HWND _hwnd;
	MSG _msg;
	LPCSTR  _className;
	RECT _rc;
};

