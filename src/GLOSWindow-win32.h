#ifndef _GL_OS_WINDOW_WIN32_H_
#define _GL_OS_WINDOW_WIN32_H_

#include "GLOSWindow.h"
#include <windows.h>

class WGLContext;
class GLOSWindowWin32 : public GLOSWindow
{
public:
	GLOSWindowWin32(void);
	virtual ~GLOSWindowWin32(void);

	// 获取设备环境
	HDC getDC();

protected:
	// 继承自父类
	virtual bool doMakeCurrent();
	virtual bool doSetTitle(const std::string& title);
	virtual bool doSetSize(const GLWindowSize& size);
	virtual bool doSetPosition(const GLWindowPos& pos);
	virtual bool doSetSizeLimit(const GLWindowSize& minSize, const GLWindowSize& maxSize);

private:
	bool init();

	bool registerWindowClass();
	void unregisterWindowClass();

	bool createWindow();

	DWORD getWindowStyle();
	DWORD getWindowExStyle();

	static bool s_initialized;

	static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND _hWnd;

	WGLContext* _context;

	friend GLOSWindow;
	friend WGLContext;
};

#endif // !_GL_OS_WINDOW_WIN32_H_