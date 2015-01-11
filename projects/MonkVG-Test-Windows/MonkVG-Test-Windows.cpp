// MonkVG-Test-Windows.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MonkVG-Test-Windows.h"
//#include <EGL/egl.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HDC   ghDC;
HGLRC ghRC;

#define SWAPBUFFERS SwapBuffers(ghDC)

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT				OnCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT				OnPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL				bSetupPixelFormat(HDC hdc);
void				drawScene(void);
void				resize(VGint width, VGint height);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MONKVGTESTWINDOWS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MONKVGTESTWINDOWS));

	/* animation loop */
	while (1) {
		/*
		*  Process all pending messages
		*/

		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE)
		{
			if (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				return TRUE;
			}
		}
		drawScene();
	}
	
	
	/*while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}*/

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MONKVGTESTWINDOWS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MONKVGTESTWINDOWS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;

	switch (message)
	{
	case WM_CREATE:
		OnCreate(hWnd, message, wParam, lParam);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
		GetClientRect(hWnd, &rect);
		resize(rect.right, rect.bottom);
		break;
	case WM_DESTROY:
		
		if (ghRC)
			wglDeleteContext(ghRC);
		if (ghDC)
			ReleaseDC(hWnd, ghDC);

		vgDestroyContextMNK();

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


LRESULT OnCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*
	LPCREATESTRUCT lpCreateStruct = (LPCREATESTRUCT)lParam;
	VGint width = lpCreateStruct->cx;
	VGint height = lpCreateStruct->cy;
	*/

	ghDC = GetDC(hWnd);
	if (!bSetupPixelFormat(ghDC))
		PostQuitMessage(0);

	ghRC = wglCreateContext(ghDC);
	wglMakeCurrent(ghDC, ghRC);


	RECT rc;
	::GetClientRect(hWnd, &rc);

	VGint width = rc.right - rc.left;
	VGint height = rc.bottom - rc.top;
	vgCreateContextMNK(width, height, VGRenderingBackendTypeMNK::VG_RENDERING_BACKEND_TYPE_OPENGLES20, (VGHandle)hWnd);

	return 0;
}

void drawScene(void)
{
	VGPaint strokePaint = vgCreatePaint();
	vgSetPaint(strokePaint, VG_STROKE_PATH);

	VGfloat color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	vgSetParameterfv(strokePaint, VG_PAINT_COLOR, 4, &color[0]);

	VGPath line = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_ALL);
	vguLine(line, 20, 20, 130, 130);

	VGPath square = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_ALL);
	vguRect(square, 10.0f, 10.0f, 130.0f, 50.0f);

	vgSetf(VG_STROKE_LINE_WIDTH, 7.0f);
	vgDrawPath(line, VG_STROKE_PATH);
	vgDrawPath(square, VG_STROKE_PATH);

	SwapBuffers(ghDC);
}

void resize(VGint width, VGint height)
{
	vgResizeSurfaceMNK(width, height);
}

//LRESULT OnPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//
//	VGPaint strokePaint = vgCreatePaint();
//	vgSetPaint(strokePaint, VG_STROKE_PATH);
//
//	VGfloat color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
//	vgSetParameterfv(strokePaint, VG_PAINT_COLOR, 4, &color[0]);
//
//	VGPath line = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_ALL);
//	vguLine(line, 20, 20, 130, 130);
//
//	VGPath square = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_ALL);
//	vguRect(square, 10.0f, 10.0f, 130.0f, 50.0f);
//
//	vgSetf(VG_STROKE_LINE_WIDTH, 7.0f);
//	vgDrawPath(line, VG_STROKE_PATH);
//	vgDrawPath(square, VG_STROKE_PATH);
//
//
//
//	::ValidateRect(hWnd, NULL);
//	return 0;
//}





// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


BOOL bSetupPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd, *ppfd;
	int pixelformat;

	ppfd = &pfd;

	ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
	ppfd->nVersion = 1;
	ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER;
	ppfd->dwLayerMask = PFD_MAIN_PLANE;
	ppfd->iPixelType = PFD_TYPE_COLORINDEX;
	ppfd->cColorBits = 8;
	ppfd->cDepthBits = 16;
	ppfd->cAccumBits = 0;
	ppfd->cStencilBits = 0;

	pixelformat = ChoosePixelFormat(hdc, ppfd);

	if ((pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0)
	{
		MessageBox(NULL, _T("ChoosePixelFormat failed"), _T("Error"), MB_OK);
		return FALSE;
	}

	if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE)
	{
		MessageBox(NULL, _T("SetPixelFormat failed"), _T("Error"), MB_OK);
		return FALSE;
	}

	return TRUE;
}