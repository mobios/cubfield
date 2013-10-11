#ifndef CPP_program_framework
#define CPP_program_framework

#include "common.h"
#include "cube.h"
#include <fstream>
#include <iostream>

struct windowClass;
struct renderClass;
struct glClass;

struct framework{
	static constexpr LPCSTR displayTitle = "Application Title";

	void finish(const global::errorCode code, const std::string* error = nullptr) const;

	const windowClass* getWindow() const;
	renderClass* getRender() const;
	HINSTANCE getHINSTANCE() const;
	WNDPROC getWNDPROC() const;

	framework(HINSTANCE, WNDPROC);
	~framework();
	
	void draw();

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

struct glClass{
protected:
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
	PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;
	
	PFNGLGENBUFFERSPROC glGenBuffers;
	PFNGLBINDBUFFERPROC glBindBuffer;
	PFNGLBUFFERDATAPROC glBufferData;
	
	PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
	PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
	PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
	
	PFNGLCREATESHADERPROC glCreateShader;
	PFNGLSHADERSOURCEPROC glShaderSource;
	PFNGLCOMPILESHADERPROC glCompileShader;
	
	PFNGLGETSHADERIVPROC glGetShaderiv;
	PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
	PFNGLCREATEPROGRAMPROC glCreateProgram;
	PFNGLATTACHSHADERPROC glAttachShader;
	PFNGLLINKPROGRAMPROC glLinkProgram;
	PFNGLGETPROGRAMIVPROC glGetProgramiv;
	PFNGLUSEPROGRAMPROC glUseProgram;
	PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
	PFNGLDELETESHADERPROC glDeleteShader;
	PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
	PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
	
};

struct renderClass: public glClass{
	renderClass(const framework*);

	void makeGLContext(const HDC hDC);
	void makeCurrent(const HDC, const bool erase = false);
	void loadExtensions(const HDC);
	void loadShaders();
	
	void upgradeContext(const HDC);
	
	void clear();
	void swapBuffers();
	void setupVertexArray(const GLfloat*, const std::size_t);
	void draw();

private:
	void finish(const global::errorCode, const std::string &);

	HGLRC hGLrc;
	const framework* parent;
	int contextState;
	
	GLuint vertexArrayID;
	GLuint vertexbuffer;
	GLuint shaderProgram;
	GLuint vertexAttributeObject;
	std::size_t vertexbuffersize;
	
};
#endif
