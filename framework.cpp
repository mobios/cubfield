#include "framework.h"

void framework::finish(const global::errorCode code, const std::string* error) const{
	if(code && error){
		std::cerr << *error << '\n' << "Code: " << code << '\n';
		exit(GetLastError());
	}
	
	exit(0);
}

const windowClass* framework::getWindow() const{
	return window;
}

renderClass* framework::getRender() const{
	return graphics;
}

HINSTANCE framework::getHINSTANCE() const{
	return hInstance;
}

WNDPROC framework::getWNDPROC() const{
	return windowProc;
}

framework::framework(HINSTANCE hInstanceParam, WNDPROC windowProcParam){
	hInstance = hInstanceParam;
	windowProc = windowProcParam;
	window = new windowClass(this);
	graphics = new renderClass(this);
	pField = new field(1,1,1);
	std::cout << "Pre gen1\n";
	pField->genVerticies();
	std::cout << "post gen\n";
	graphics->setupVertexArray(pField->getVerticies(), pField->vertexArraySize());
	window->makeAvailable();
}

framework::~framework(){
	if(window)
		delete window;
	if(graphics)
		delete graphics;
}

void framework::draw(){
	graphics->draw();
}

windowClass::windowClass(const framework* parentParam){
	parent = parentParam;
	makeClass(parentParam->getHINSTANCE(), parentParam->getWNDPROC(), parentParam->displayTitle);
	createWindow(parentParam->getHINSTANCE(), parentParam->getWNDPROC(), parentParam->displayTitle, parentParam->displayTitle);
}

void windowClass::makeClass(HINSTANCE hInstance, const WNDPROC windowProc, const LPCSTR className){
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = windowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;
	
	if(!RegisterClass(&wc)){
		std::string error = "Class could not register";
		parent->finish(global::errorCode::PREWINDOW, &error);
	}
}

void windowClass::createWindow(HINSTANCE hInstance, const WNDPROC windowProc, const LPCSTR className, const LPCSTR windowName){
	hWnd = CreateWindow(className,
						windowName,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						hInstance,
						NULL);
	if(hWnd == NULL){
		std::string error = "Could not create window";
		parent->finish(global::errorCode::PREWINDOW, &error);
	}
	hDC = GetDC(hWnd);
	if(!hDC){
		std::string error = "Could not get device context";
		parent->finish(global::errorCode::PRECONTEXT, &error);
	}
}

void windowClass::makeAvailable(){
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
}

renderClass::renderClass(const framework* parentParam){
	parent = parentParam;
	contextState = global::glstate::NONE;
	hGLrc = NULL;
	
	const HDC hDC = parentParam->getWindow()->getHDC();
	makeGLContext(hDC);
	loadExtensions(hDC);
	upgradeContext(hDC);
	loadShaders();
}

void renderClass::makeGLContext(const HDC hDC){	
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
	if(!nPixelFormat)
		finish(global::errorCode::PRECONTEXT, "Pixel format was not matched");
	
	
	if(!SetPixelFormat(hDC, nPixelFormat, &pfd))
		finish(global::errorCode::PRECONTEXT, "Pixel format could not be set");
	
	
	hGLrc = wglCreateContext(hDC);
	if(!hGLrc)
		finish(global::errorCode::PRECONTEXT, "Could not create GL context");
	makeCurrent(hDC);
	contextState = global::glstate::PREUPGRADE;
}

void renderClass::makeCurrent(const HDC hDC, const bool erase){
	if(!erase){
		wglMakeCurrent(hDC, hGLrc);
		return;
	}

	wglMakeCurrent(NULL, NULL);
	if(hGLrc){
		wglDeleteContext(hGLrc);
		hGLrc = NULL;
	}
}

void renderClass::loadExtensions(const HDC hDC){
	if(contextState == global::glstate::NONE)
		return;
		
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC) wglGetProcAddress("wglGetExtensionsStringARB");
	const char* extensions = wglGetExtensionsStringARB(hDC);
	
	if(!strstr(extensions, "WGL_ARB_create_context"))
		finish(global::errorCode::PRECONTEXTUPGRADE, "OpenGL 3/4 is not supported");
		
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");
	glGenBuffers = (PFNGLGENBUFFERSPROC) wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC) wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC) wglGetProcAddress("glBufferData");
	
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) wglGetProcAddress("glEnableVertexAttribArray");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) wglGetProcAddress("glVertexAttribPointer");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) wglGetProcAddress("glDisableVertexAttribArray");
	
	contextState = global::glstate::LOAD;	
	std::cout << "Done loading\n";
}

void renderClass::upgradeContext(const HDC hDC){
	if(contextState != global::glstate::LOAD)
		finish(global::errorCode::PRECONTEXTUPGRADE, "Functions not loaded");
		
	int gla[] = {	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
					WGL_CONTEXT_MINOR_VERSION_ARB, 1,
					WGL_CONTEXT_FLAGS_ARB, 0,
					0
	};
	
	HGLRC tempHGLRC = wglCreateContextAttribsARB(hDC, 0, gla);
	if(!tempHGLRC)
		finish(global::errorCode::PRECONTEXTUPGRADE, "Could not upgrade context");
		
	makeCurrent(hDC, true);
	hGLrc = tempHGLRC;
	makeCurrent(hDC, hGLrc);
}

void renderClass::finish(const global::errorCode code, const std::string &error){
	parent->finish(code, &error);
}

void renderClass::clear(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderClass::swapBuffers(){
	SwapBuffers(parent->getWindow()->getHDC());
}

void renderClass::setupVertexArray(const GLfloat* array, const std::size_t size){
	std::cout << "Pre gen\n";
	glGenBuffers(1, &vertexbuffer);
	std::cout << "Pre buffer bind\n";
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	std::cout << "post buffer bind\n";
	glBufferData(GL_ARRAY_BUFFER, size, array, GL_STATIC_DRAW);
	vertexbuffersize = size;
}

void renderClass::draw(){
	clear();
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,
		vertexbuffersize,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	
	glDrawArrays(GL_TRIANGLES, 0, vertexbuffersize);
	glDisableVertexAttribArray(0);
	swapBuffers();
}

void renderClass::loadShaders(){
	constexpr char* vShaderFile = "vertex.glsl";
	constexpr char* fShaderFile = "fragment.glsl";
	
	const GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	const GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	
	std::string vertexShader;
	std::ifstream vShaderStream
	if(!vShaderStream.is_open){
		std::string msg = "Vertex shader not found";
		parent->finish(global::errorCode::PRESHADER, &msg);
	}
	
	std::string line;
	while(getline(vShaderStream, line)
		vertexShader += line + "\n";
	vShaderStream.close();
	
	std::string fragmentShader;
	std::ifstream fShaderStream
	if(!fShaderStream.is_open){
		std::string msg = "Fragment shader not found";
		parent->finish(global::errorCode::PRESHADER, &msg);
	}
	
	std::string line;
	while(getline(fShaderStream, line)
		fragmentShader += line + "\n";
	fShaderStream.close();
	
	GLint compResult = GL_FALSE;
	int logLength;
	
	glShaderSource(vertexShaderID, 1, &(vertexShader.c_str()), NULL);
	glCompileShader(vertexShaderID);
	
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &compResult);
	glGetShaderiv(
	
	