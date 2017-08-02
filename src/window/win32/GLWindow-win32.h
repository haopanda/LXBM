#ifndef _GL_OS_WINDOW_WIN32_H_
#define _GL_OS_WINDOW_WIN32_H_

#include "window/GLWindow.h"
#include <Windows.h>

class WGLContext;
class GLWindowWin32 : public GLWindow
{
public:
	static GLWindowWin32* create();

	GLWindowWin32(void);
	virtual ~GLWindowWin32(void);

	// 获取设备环境
	HDC getDC();

protected:
	// 继承自父类
	virtual bool doMakeCurrent() override;
	virtual bool doSetTitle(const std::string& title) override;
	virtual bool doSetSize(const GLWindowSize& size) override;
	virtual bool doSetPosition(const GLWindowPos& pos) override;
	virtual bool doSetSizeLimit(const GLWindowSize& minSize, const GLWindowSize& maxSize) override;
	virtual void doSetVisible(bool visible) override;

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

	friend GLWindow;
	friend WGLContext;
};

#endif // !_GL_OS_WINDOW_WIN32_H_