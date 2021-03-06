#ifndef _WGL_CONTEXT_H_
#define _WGL_CONTEXT_H_

#include "window/GLContext.h"
#include <windows.h>

class GLWindowWin32;

class WGLContext : public GLContext
{
public:
	static WGLContext* create(GLWindowWin32* window);

	static bool initWGLExtension(HWND handler);

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

	//////////////////////////////////////////////////////////////////////////
	typedef BOOL(WINAPI * PFNWGLSWAPINTERVALEXTPROC)(int);
	typedef BOOL(WINAPI * PFNWGLGETPIXELFORMATATTRIBIVARBPROC)(HDC, int, int, UINT, const int*, int*);
	typedef const char* (WINAPI * PFNWGLGETEXTENSIONSSTRINGEXTPROC)(void);
	typedef const char* (WINAPI * PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC);
	typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);

	typedef HGLRC(WINAPI * PFN_wglCreateContext)(HDC);
	typedef BOOL(WINAPI * PFN_wglDeleteContext)(HGLRC);
	typedef PROC(WINAPI * PFN_wglGetProcAddress)(LPCSTR);
	typedef HDC(WINAPI * PFN_wglGetCurrentDC)(void);
	typedef BOOL(WINAPI * PFN_wglMakeCurrent)(HDC, HGLRC);
	typedef BOOL(WINAPI * PFN_wglShareLists)(HGLRC, HGLRC);

	struct WGLLibrary
	{
		HINSTANCE instance;
		PFN_wglCreateContext                CreateContext;
		PFN_wglDeleteContext                DeleteContext;
		PFN_wglGetProcAddress               GetProcAddress;
		PFN_wglGetCurrentDC                 GetCurrentDC;
		PFN_wglMakeCurrent                  MakeCurrent;
		PFN_wglShareLists                   ShareLists;

		PFNWGLSWAPINTERVALEXTPROC           SwapIntervalEXT;
		PFNWGLGETPIXELFORMATATTRIBIVARBPROC GetPixelFormatAttribivARB;
		PFNWGLGETEXTENSIONSSTRINGEXTPROC    GetExtensionsStringEXT;
		PFNWGLGETEXTENSIONSSTRINGARBPROC    GetExtensionsStringARB;
		PFNWGLCREATECONTEXTATTRIBSARBPROC   CreateContextAttribsARB;

		bool                                EXT_swap_control;
		bool                                EXT_colorspace;
		bool                                ARB_multisample;
		bool                                ARB_framebuffer_sRGB;
		bool                                EXT_framebuffer_sRGB;
		bool                                ARB_pixel_format;
		bool                                ARB_create_context;
		bool                                ARB_create_context_profile;
		bool                                EXT_create_context_es2_profile;
		bool                                ARB_create_context_robustness;
		bool                                ARB_create_context_no_error;
		bool                                ARB_context_flush_control;
	};
	static WGLLibrary* s_wglLibrary;

	static bool initWGLLibrary(HDC hDC);
	//////////////////////////////////////////////////////////////////////////
};

#endif // !_WGL_CONTEXT_H_

