#include<Windows.h>
#include<iostream>
#include"Graphics.h"
#include"Root.h"
#include<sstream>



//プロトタイプ宣言
bool CreateMainWindow(HWND&, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

//グローーーーバル変数
Root* g_root;
HWND hWnd = NULL;

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow) {

	MSG msg;
	g_root = new Root();

	if (!CreateMainWindow(hWnd, hInstance, nCmdShow)) {
		return -1;
	}
	g_root->initialize(hWnd);
	try {
		//メインメッセージループ
		do {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				g_root->run(hWnd);
			}
			
		} while (msg.message != WM_QUIT);
		DELETE(g_root);
		return msg.wParam;
	}
	catch (...) {
		g_root->deleteAll();
		DestroyWindow(hWnd);
		//WARN("メインループでエラー");
	}
	DELETE(g_root);
	return 0;
}


LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return (g_root->messageHandler(hWnd, msg, wParam, lParam));
}

bool CreateMainWindow(HWND& hWnd, HINSTANCE hInstance, int nCmdShow) {
	WNDCLASSEX wcx;

	// Fill in the window class structure with parameters 
	// that describe the main window. 
	wcx.cbSize = sizeof(wcx);           // size of structure 
	wcx.style = CS_HREDRAW | CS_VREDRAW;    // redraw if size changes 
	wcx.lpfnWndProc = WinProc;          // points to window procedure 
	wcx.cbClsExtra = 0;                 // no extra class memory 
	wcx.cbWndExtra = 0;                 // no extra window memory 
	wcx.hInstance = hInstance;          // handle to instance 
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);   // predefined arrow 
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);    // black background 
	wcx.lpszMenuName = NULL;            // name of menu resource 
	wcx.lpszClassName = CLASS_NAME;     // name of window class 
	wcx.hIconSm = NULL;

	// Register the window class. 
	// RegisterClassEx returns 0 on error.
	if (RegisterClassEx(&wcx) == 0) {  // if error
		return false;
	}

	// Create window
	DWORD style = 0;
	if (FULLSCREEN) {
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}
	else {
		style = WS_OVERLAPPEDWINDOW;
	}
	hWnd = CreateWindow(
		CLASS_NAME,             // name of the window class
		GAME_TITLE,             // title bar text
		style,    // window style
		CW_USEDEFAULT,          // default horizontal position of window
		CW_USEDEFAULT,          // default vertical position of window
		WINDOW_WIDTH,             // width of window
		WINDOW_HEIGHT,            // height of the window
		(HWND)NULL,            // no parent window
		(HMENU)NULL,           // no menu
		hInstance,              // handle to application instance
		(LPVOID)NULL);         // no window parameters

							   // if there was an error creating the window
	if (!hWnd) {
		return false;
	}

	if (!FULLSCREEN) {
		RECT rect;
		GetClientRect(hWnd, &rect);
		int w = WINDOW_WIDTH + (WINDOW_WIDTH - rect.right);
		int h = WINDOW_HEIGHT + (WINDOW_HEIGHT - rect.bottom);
		MoveWindow(hWnd, 0, 0, w, h, TRUE);
	}


	// Show the window
	ShowWindow(hWnd, nCmdShow);

	// Send a WM_PAINT message to the window procedure
	return true;
}