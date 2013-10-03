#include "common.h"
#include "framework.h"
#include <GL\gl.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	framework frame(hInstance, WindowProc);
	//HWND hWnd = frame.window->createwindow(&hInstance, WindowProc, frame.displayTitle, "Test");
	/*if(!hWnd){
		std::string error = "No window";
		frame.finish(false, global::errorCode::PREWINDOW, &error);
	}
	HDC hDC = GetDC(hWnd);
	
	if(!hDC){
		std::string error = "Could not get Device Context";
		frame.finish(false, global::errorCode::PRECONTEXT, &error);
	}
	
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;
	
	int nPixelFormat = ChoosePixelFormat(hDC, &pfd);
	if(!nPixelFormat){
		std::string error = "Pixel format was not matched";
		frame.finish(false, global::errorCode::PRECONTEXT);
	}
	
	if(!SetPixelFormat(hDC, nPixelFormat, &pfd)){
		std::string error = "Pixel format could not be set";
		frame.finish(false, global::errorCode::PRECONTEXT);
	}
	
	HGLRC dctxt = wglCreateContext(hDC);
	wglMakeCurrent(hDC, dctxt);
	gl::wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC) wglGetProcAddress("wglGetExtensionsStringARB");
	const char* extensions = gl::wglGetExtensionsStringARB(hDC);
	
	if(!strstr(extensions, "WGL_ARB_create_context")){
		std::string error = "OpenGL 3/4 is not supported";
		frame.finish(false, global::errorCode::PRECONTEXTUPGRADE);
	}
	
	gl::wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");
	int gla[] = {	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
					WGL_CONTEXT_MINOR_VERSION_ARB, 1,
					WGL_CONTEXT_FLAGS_ARB, 0,
					0
	};
	
	HGLRC nHRC = gl::wglCreateContextAttribsARB(hDC, 0, gla);
	if(!nHRC){
		std::string error = "OpenGL context switch did not complete";
		frame.finish(false, global::errorCode::PRECONTEXTUPGRADE);
	}
	
	wglMakeCurrent(NULL,NULL);
	wglDeleteContext(dctxt);
	wglMakeCurrent(hDC, nHRC); */
	//frame.window->makeAvailable();
	
	MSG msg;
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
