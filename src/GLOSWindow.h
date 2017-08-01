#ifndef _GL_OS_WINDOW_H_
#define _GL_OS_WINDOW_H_

#include <string>

// 窗口大小
struct GLWindowSize
{
	int width;
	int height;
};

// 窗口坐标
struct GLWindowPos
{
	int x;
	int y;
};

class GLOSWindow
{
public:
	// 在不同平台的实现中定义 
	static GLOSWindow* create();

	// 成为当前渲染窗口 
	bool makeCurrent();

	// 设置窗口标题
	bool setTitle(const std::string& title);

	// 设置窗口大小
	bool setSize(const GLWindowSize& size);

	// 设置窗口位置
	bool setPosition(const GLWindowPos& pos);

	// 设置窗口大小限制
	bool setSizeLimit(const GLWindowSize& minSize, const GLWindowSize& maxSize);

	// 窗口是否应该关闭
	bool windowShouldClose() { return _shouldClose; };

protected:
	// 点击了窗口的关闭按钮
	void onWindowShouldClose();

protected:
	virtual bool doMakeCurrent() = 0;
	virtual bool doSetTitle(const std::string& title) { return true; };
	virtual bool doSetSize(const GLWindowSize& size) { return true; };
	virtual bool doSetPosition(const GLWindowPos& pos) { return true; };
	virtual bool doSetSizeLimit(const GLWindowSize& minSize, const GLWindowSize& maxSize) { return true; };

private:
	static GLOSWindow* s_currentWindow;
	
	std::string _title;
	GLWindowSize _size;
	GLWindowSize _minSize;
	GLWindowSize _maxSize;
	GLWindowPos _pos;
	bool _shouldClose;
};

#endif // !_GL_OS_WINDOW_H_