#include "GLOSWindow-win32.h"
#include "WGLContext.h"
#include "Win32Helper.h"
#include <new>

GLOSWindow* GLOSWindow::create()
{
	auto pRet = new (std::nothrow) GLOSWindowWin32();
	if (pRet && pRet->init())
	{
		return pRet;
	}
	if (pRet) delete pRet;
	return nullptr;
}

////////////////////////////////
#define _WINDOW_CLASS_NAME L"LXBM"

bool GLOSWindowWin32::s_initialized = false;

GLOSWindowWin32::GLOSWindowWin32()
{
	//
}

GLOSWindowWin32::~GLOSWindowWin32()
{
	//
}

bool GLOSWindowWin32::init()
{
	if (!GLOSWindowWin32::s_initialized)
	{
		if (!this->registerWindowClass())
			return false;

		GLOSWindowWin32::s_initialized = true;
	}

	if (!createWindow())
	{
		return false;
	}

	_context = WGLContext::create(this);
	if (!_context)
	{
		return false;
	}

	_context->makeCurrent();

	return true;
}

// ע�ᴰ����
bool GLOSWindowWin32::registerWindowClass()
{
	WNDCLASSEXW wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = GLOSWindowWin32::windowProc;
	wc.hInstance = GetModuleHandleW(NULL);
	wc.lpszClassName = _WINDOW_CLASS_NAME;

	if (!RegisterClassExW(&wc))
		return false;

	return true;
}

// ע��������
void GLOSWindowWin32::unregisterWindowClass()
{
	UnregisterClassW(_WINDOW_CLASS_NAME, GetModuleHandleW(NULL));
}

// ��������
bool GLOSWindowWin32::createWindow()
{
	_hWnd = CreateWindowExW(getWindowStyle(),
		                    _WINDOW_CLASS_NAME,
		                    L"LXBM",
		                    getWindowExStyle(),
		                    CW_USEDEFAULT,
		                    CW_USEDEFAULT,
		                    CW_USEDEFAULT,
		                    CW_USEDEFAULT,
		                    NULL,
		                    NULL,
		                    GetModuleHandleW(NULL),
		                    NULL);
	if (!_hWnd)
		return false;

	SetPropW(_hWnd, L"LXBM", this);

	ChangeWindowMessageFilterEx(_hWnd, WM_DROPFILES, MSGFLT_ALLOW, NULL);
	ChangeWindowMessageFilterEx(_hWnd, WM_COPYDATA, MSGFLT_ALLOW, NULL);
	//ChangeWindowMessageFilterEx(_hWnd, WM_COPYGLOBALDATA, MSGFLT_ALLOW, NULL);
	DragAcceptFiles(_hWnd, TRUE);

	return true;
}

HDC GLOSWindowWin32::getDC()
{
	return GetDC(_hWnd);
}

DWORD GLOSWindowWin32::getWindowStyle()
{
	return WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP;
}

DWORD GLOSWindowWin32::getWindowExStyle()
{
	return WS_EX_APPWINDOW;
}

bool GLOSWindowWin32::doMakeCurrent()
{
	return _context->makeCurrent();
}

bool GLOSWindowWin32::doSetTitle(const std::string& title)
{
	auto wstr = Win32Helper::convertUTF8ToWideString(title);
	if (wstr.size() > 0)
	{
		return SetWindowTextW(_hWnd, wstr.c_str());
	}
	return false;
}

bool GLOSWindowWin32::doSetSize(const GLWindowSize& size)
{
	RECT rect = { 0, 0, size.width, size.height };
	AdjustWindowRectEx(&rect, getWindowStyle(), FALSE, getWindowExStyle());
	SetWindowPos(_hWnd, HWND_TOP, 0, 0,
		         rect.right - rect.left, rect.bottom - rect.top,
		         SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER);
	return true;
}

bool GLOSWindowWin32::doSetPosition(const GLWindowPos& pos)
{
	RECT rect = { pos.x, pos.y, pos.x, pos.y };
	AdjustWindowRectEx(&rect, getWindowExStyle(), FALSE, getWindowExStyle());
	SetWindowPos(_hWnd, HWND_TOP, rect.right, rect.top, 0, 0,
		         SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
	return true;
}

bool GLOSWindowWin32::doSetSizeLimit(const GLWindowSize& minSize, const GLWindowSize& maxSize)
{
	RECT rect;
	GetWindowRect(_hWnd, &rect);
	MoveWindow(_hWnd, rect.left, rect.top, 
		       rect.right - rect.left, 
		       rect.bottom - rect.top, TRUE);
	return true;
}

LRESULT CALLBACK GLOSWindowWin32::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	GLOSWindowWin32* window = (GLOSWindowWin32*)GetPropW(hWnd, L"LXBM");

	if (!window)
	{
		return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}

	switch (uMsg)
	{
	case WM_CLOSE:
		window->onWindowShouldClose();
		return 0;
	default:
		break;
	}
}