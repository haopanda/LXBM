#ifndef _WINDOW_MANAGER_WIN32_H_
#define _WINDOW_MANAGER_WIN32_H_

#include "window/WindowManager.h"

class WindowManagerWin32 : public WindowManager
{
public:
	virtual ~WindowManagerWin32();

protected:
	WindowManagerWin32();

	// ∏∏¿‡ºÃ≥–
	virtual bool init() override;
	virtual GLWindow* doCreateWindow() const override;
	virtual void doPollEvents() override;
	virtual void doWaitEvents() override;

	friend class WindowManager;
};

#endif // !_WINDOW_MANAGER_WIN32_H_