#ifndef CPP_program_COMMON
#define CPP_program_COMMON

#include <windows.h>
#include <string>
#include <GL\gl.h>
#include <GL\glext.h>
#include <GL\wglext.h>
#define PARAM_DEBUG

#define loadGL(func, ptrtype) func = (ptrtype) wglGetProcAddress(#func)
#ifdef PARAM_DEBUG
	#define __debug(message, value) std::cout << #message << value << std::endl;
#else
	#define __debug(message, value) ;
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
