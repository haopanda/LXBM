#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

#include "GLWindow.h"
#include <vector>

class WindowManager
{
public:
	static WindowManager* getInstance();
	static void destroyInstance(void);

	virtual ~WindowManager();

	GLWindow* createWindow();

	std::vector<GLWindow*>& getAllWindows() { return _windows; };

	// 处理所有已经在事件队列中的窗口事件，立即返回
	void pollEvents();

	// 调用线程进入睡眠状态，直到事件队列中有至少一个事件
	// 然后处理这些事件并返回.
	void waitEvents();

protected:
	WindowManager(void);

	// 创建平台特定实例，在平台相关文件中定义
	static WindowManager* createNativeInstance();

	virtual bool init();
	virtual GLWindow* doCreateWindow() const = 0;
	virtual void doPollEvents() = 0;
	virtual void doWaitEvents() = 0;
	
private:
	static WindowManager* s_instance;

	std::vector<GLWindow*> _windows;
};

#endif // !_WINDOW_MANAGER_H_