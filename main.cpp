#include "common.h"
#include "framework.h"
#include <GL\gl.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	framework frame(hInstance, WindowProc);
	
	MSG msg;
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		
		frame.getRender()->draw();
	}
}
