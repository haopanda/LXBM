#ifndef _WGL_CONTEXT_H_
#define _WGL_CONTEXT_H_

#include "window/GLContext.h"
#include <windows.h>

class GLWindowWin32;

class WGLContext : public GLContext
{
public:
	static WGLContext* create(GLWindowWin32* window);

	// 实现父类方法
	virtual bool makeCurrent(void);
	virtual void swapBuffers(void);

private:
	bool init(GLWindowWin32* window);
	int getPixelFormatAttrib(int pixelFormat, int attrib);

	int choosePixelFormat(GLWindowWin32* window, const FBConfig& fbConfig);

private:
	HDC _hDC;
	HGLRC _hRC;
	/*typedef HGLRC(WINAPI * PFN_wglCreateContext)(HDC);
	typedef BOOL(WINAPI * PFN_wglDeleteContext)(HGLRC);
	typedef PROC(WINAPI * PFN_wglGetProcAddress)(LPCSTR);
	typedef HDC(WINAPI * PFN_wglGetCurrentDC)(void);
	typedef BOOL(WINAPI * PFN_wglMakeCurrent)(HDC, HGLRC);
	typedef BOOL(WINAPI * PFN_wglShareLists)(HGLRC, HGLRC);

	static HINSTANCE s_instance;
	static PFN_wglCreateContext wglCreateContext;
	static PFN_wglDeleteContext wglDeleteContext;
	static PFN_wglGetProcAddress wglGetProcAddress;
	static PFN_wglGetCurrentDC wglGetCurrentDC;
	static PFN_wglMakeCurrent wglMakeCurrent;
	static PFN_wglShareLists wglShareLists;*/
};

#endif // !_WGL_CONTEXT_H_

