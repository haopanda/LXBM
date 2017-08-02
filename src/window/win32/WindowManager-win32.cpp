#include "WindowManager-win32.h"
#include "window/win32/GLWindow-win32.h"

#include <windows.h>
#include <new>

WindowManager* WindowManager::createNativeInstance()
{
	auto pRet = new (std::nothrow) WindowManagerWin32();
	if (pRet && pRet->init())
	{
		return pRet;
	}
	if (pRet) delete pRet;

	return nullptr;
}

WindowManagerWin32::WindowManagerWin32()
{
	// todo
}

WindowManagerWin32::~WindowManagerWin32()
{
	// todo
}

bool WindowManagerWin32::init()
{
	return true;
}

GLWindow* WindowManagerWin32::doCreateWindow() const
{
	return GLWindowWin32::create();
}

void WindowManagerWin32::doPollEvents()
{
	MSG msg;
	while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			auto windows = getAllWindows();
			for (auto iter = windows.begin(); iter != windows.end(); ++iter)
			{
				(*iter)->onWindowShouldClose();
			}
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
}

void WindowManagerWin32::doWaitEvents()
{
	WaitMessage();
	doPollEvents();
}