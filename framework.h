#ifndef CPP_program_framework
#define CPP_program_framework

#include "common.h"
#include "cube.h"
struct windowClass;
struct renderClass;
struct glClass;

struct framework{
	static constexpr LPCSTR displayTitle = "Application Title";

	void finish(const global::errorCode code, const std::string* error = nullptr) const;

	const windowClass* getWindow() const;
	const renderClass* getRender() const;
	HINSTANCE getHINSTANCE() const;
	WNDPROC getWNDPROC() const;

	framework(HINSTANCE, WNDPROC);
	~framework();

private:
	windowClass* window;
	renderClass* graphics;
	field* pField;
	HINSTANCE hInstance;
	WNDPROC windowProc;
};

struct windowClass{
	windowClass(const framework*);

	void makeClass(HINSTANCE, const WNDPROC, const LPCSTR);
	void createWindow(HINSTANCE, const WNDPROC, const LPCSTR, const LPCSTR);
	void makeAvailable();

	const HDC getHDC() const {return hDC;};
	const HWND getHWND()const {return hWnd;};

private:
	const framework* parent;
	HWND hWnd;
	HDC  hDC;
};

struct renderClass{
	renderClass(const framework*);

	void makeGLContext(const HDC hDC);
	void makeCurrent(const HDC, const bool erase = false);
	void loadExtensions(const HDC);
	void upgradeContext(const HDC);

private:
	void finish(const global::errorCode, const std::string &);

	HGLRC hGLrc;
	const framework* parent;
	int contextState;
	glClass* gl;
};

struct glClass{
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
	PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;
};
#endif
