#include "WGLContext.h"
#include "GLWindow-win32.h"

#include <Wingdi.h>
#include <vector>

#define wglCreateContext s_wglLibrary->CreateContext
#define wglDeleteContext s_wglLibrary->DeleteContext
#define wglMakeCurrent s_wglLibrary->MakeCurrent
#define wglGetProcAddress s_wglLibrary->GetProcAddress

WGLContext::WGLLibrary* WGLContext::s_wglLibrary = nullptr;

WGLContext* WGLContext::create(GLWindowWin32* window)
{
	auto pRet = new (std::nothrow) WGLContext();
	if (pRet && pRet->init(window))
	{
		return pRet;
	}
	if (pRet) delete pRet;

	return nullptr;
}

bool WGLContext::initWGLLibrary(HDC hDC)
{
	if (s_wglLibrary != nullptr)
	{
		return true;
	}
	s_wglLibrary = new (std::nothrow) WGLLibrary();
	if (s_wglLibrary == nullptr)
	{
		return false;
	}

	s_wglLibrary->instance = LoadLibraryA("opengl32.dll");
	if (!s_wglLibrary->instance)
	{
		return false;
	}
	s_wglLibrary->CreateContext = reinterpret_cast<PFN_wglCreateContext>(GetProcAddress(s_wglLibrary->instance, "wglCreateContext"));
	s_wglLibrary->DeleteContext = reinterpret_cast<PFN_wglDeleteContext>(GetProcAddress(s_wglLibrary->instance, "wglDeleteContext"));
	s_wglLibrary->GetProcAddress = reinterpret_cast<PFN_wglGetProcAddress>(GetProcAddress(s_wglLibrary->instance, "wglGetProcAddress"));
	s_wglLibrary->GetCurrentDC = reinterpret_cast<PFN_wglGetCurrentDC>(GetProcAddress(s_wglLibrary->instance, "wglGetCurrentDC"));
	s_wglLibrary->MakeCurrent = reinterpret_cast<PFN_wglMakeCurrent>(GetProcAddress(s_wglLibrary->instance, "wglMakeCurrent"));
	s_wglLibrary->ShareLists = reinterpret_cast<PFN_wglShareLists>(GetProcAddress(s_wglLibrary->instance, "wglShareLists"));

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;

	if (!SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd))
	{
		return false;
	}

	auto rc = wglCreateContext(hDC);
	if (!rc)
		return false;

	if (!wglMakeCurrent(hDC, rc))
	{
		wglDeleteContext(rc);
		return false;
	}

	s_wglLibrary->GetExtensionsStringEXT = reinterpret_cast<PFNWGLGETEXTENSIONSSTRINGEXTPROC>(wglGetProcAddress("wglGetExtensionsStringEXT"));
	s_wglLibrary->GetExtensionsStringARB = reinterpret_cast<PFNWGLGETEXTENSIONSSTRINGARBPROC>(wglGetProcAddress("wglGetExtensionsStringARB"));
	s_wglLibrary->GetPixelFormatAttribivARB = reinterpret_cast<PFNWGLGETPIXELFORMATATTRIBIVARBPROC>(wglGetProcAddress("wglGetPixelFormatAttribivARB"));
	s_wglLibrary->SwapIntervalEXT = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(wglGetProcAddress("wglSwapIntervalEXT"));
	s_wglLibrary->CreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
}

bool WGLContext::init(GLWindowWin32* window)
{
	_hDC = window->getDC();
	if (!_hDC)
		return false;

	if (!initWGLLibrary(_hDC))
		return false;

	FBConfig fbConfig;
	auto pixelFormat = choosePixelFormat(window, fbConfig);
	if (pixelFormat == 0)
		return false;

	PIXELFORMATDESCRIPTOR pfd;

	if (!DescribePixelFormat(_hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd))
	{
		return false;
	}

	if (!SetPixelFormat(_hDC, pixelFormat, &pfd))
	{
		return false;
	}

	_hRC = wglCreateContext(_hDC);

	return true;
}

bool WGLContext::makeCurrent()
{
	return wglMakeCurrent(_hDC, _hRC) == TRUE;
}

void WGLContext::swapBuffers()
{
	SwapBuffers(_hDC);
}

int WGLContext::choosePixelFormat(GLWindowWin32* window, const FBConfig& fbConfig)
{
	std::vector<FBConfig> usableConfigs;
	auto nativeCount = DescribePixelFormat(_hDC, 1, sizeof(PIXELFORMATDESCRIPTOR), NULL);

	FBConfig u;
	for (auto i = 1; i <= nativeCount; ++i)
	{
		PIXELFORMATDESCRIPTOR pfd;
		if (!DescribePixelFormat(_hDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd))
		{
			continue;
		}

		if (!(pfd.dwFlags & PFD_DRAW_TO_WINDOW) ||
			!(pfd.dwFlags & PFD_SUPPORT_OPENGL))
		{
			continue;
		}

		if (!(pfd.dwFlags & PFD_GENERIC_ACCELERATED) &&
			(pfd.dwFlags & PFD_GENERIC_FORMAT))
		{
			continue;
		}

		if (pfd.iPixelType != PFD_TYPE_RGBA)
		{
			continue;
		}

		u.redBits = pfd.cRedBits;
		u.greenBits = pfd.cGreenBits;
		u.blueBits = pfd.cBlueBits;
		u.alphaBits = pfd.cAlphaBits;

		u.depthBits = pfd.cDepthBits;
		u.stencilBits = pfd.cStencilBits;

		u.accumRedBits = pfd.cAccumRedBits;
		u.accumGreenBits = pfd.cAccumGreenBits;
		u.accumBlueBits = pfd.cAccumBlueBits;
		u.accumAlphaBits = pfd.cAccumAlphaBits;

		u.auxBuffers = pfd.cAuxBuffers;

		u.stereo = (pfd.dwFlags & PFD_STEREO) > 0;
		u.doubleBuffer = pfd.dwFlags & PFD_DOUBLEBUFFER;

		usableConfigs.push_back(u);
	}

	if (usableConfigs.size() == 0)
	{
		return 0;
	}

	auto closest = chooseFBConfig(fbConfig, usableConfigs);
	if (closest == -1)
	{
		return 0;
	}
	return usableConfigs[closest].handle;
}

int WGLContext::getPixelFormatAttrib(int pixelFormat, int attrib)
{
	int value = 0;
	//if (wglGetPixelFormatAttribivARB)
	return 0;
}