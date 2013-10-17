#ifndef CPP_program_framework
#define CPP_program_framework

#include "common.h"
#include "cube.h"
#include <fstream>

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
	static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
	static PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;

	static PFNGLGENBUFFERSPROC glGenBuffers;
	static PFNGLBINDBUFFERPROC glBindBuffer;
	static PFNGLBUFFERDATAPROC glBufferData;
	
	static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
	static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
	static PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
	
	static PFNGLCREATESHADERPROC glCreateShader;
	static PFNGLSHADERSOURCEPROC glShaderSource;
	static PFNGLCOMPILESHADERPROC glCompileShader;
	
	static PFNGLGETSHADERIVPROC glGetShaderiv;
	static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
	static PFNGLCREATEPROGRAMPROC glCreateProgram;
	static PFNGLATTACHSHADERPROC glAttachShader;
	static PFNGLLINKPROGRAMPROC glLinkProgram;
	static PFNGLGETPROGRAMIVPROC glGetProgramiv;
	static PFNGLUSEPROGRAMPROC glUseProgram;
	static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
	static PFNGLDELETESHADERPROC glDeleteShader;
	static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
	static PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
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
	std::size_t numTriangles;
	
};
#endif
