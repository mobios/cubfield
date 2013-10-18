#ifndef CPP_program_COMMON
#define CPP_program_COMMON

#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>

#include <GL\gl.h>
#include <GL\glext.h>
#include <GL\wglext.h>
#define PARAM_DEBUG

#define __loadGL(func, ptrtype) func = (ptrtype) wglGetProcAddress(#func)
#define __loadResource(type, specifier) "resource/type/specifier"

#ifdef PARAM_DEBUG
	#define __debugP(message) {std::cout << DEBUG_FORMAT << DEBUG_SPACING << #message << "[OK]" << std::endl;};
	#define __debug(message, value) {std::cout << DEBUG_FORMAT << DEBUG_SPACING << #message << value << std::endl;};
	#define __debugGL(message) {auto e =glGetError(); std::cout << DEBUG_FORMAT << DEBUG_SPACING << #message << std::hex; if(e) std::cout << e; else std::cout << "[OK]"; std::cout << std::dec << std::endl;};
	#define DEBUG_SPACING std::setw(100)
	#define DEBUG_FORMAT std::setiosflags(std::ios::left | std::ios::showbase | std::ios::uppercase) << std::setfill('.')
#else
	#define __debugP(message, value) ;
	#define __debug(message, value) ;
	#define __debugGL(message, value) ;
#endif
//#include <GLM\glm.hpp>

typedef HGLRC (APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);

namespace global{
	namespace application{
		const std::string name = "AstroidField";
	}

	enum errorCode{
		PREWINDOW =1,
		PRECONTEXT,
		PRECONTEXTUPGRADE,
		PRESHADER
	};

	enum glstate{
		NONE,
		PREUPGRADE,
		LOAD,
		FULL
	};
}

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#endif
