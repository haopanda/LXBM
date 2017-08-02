#ifndef _GL_OS_WINDOW_H_
#define _GL_OS_WINDOW_H_

#include <string>

// ���ڴ�С
struct GLWindowSize
{
	int width;
	int height;
};

// ��������
struct GLWindowPos
{
	int x;
	int y;
};

class GLWindow
{
public:
	// ��Ϊ��ǰ��Ⱦ���� 
	bool makeCurrent();

	// ���ô��ڱ���
	bool setTitle(const std::string& title);

	// ���ô��ڴ�С
	bool setSize(const GLWindowSize& size);

	// ���ô���λ��
	bool setPosition(const GLWindowPos& pos);

	// ���ô��ڴ�С����
	bool setSizeLimit(const GLWindowSize& minSize, const GLWindowSize& maxSize);

	// ���ô����Ƿ���ʾ
	void setVisible(bool visible);

	// �����Ƿ�Ӧ�ùر�
	bool windowShouldClose() { return _shouldClose; };

	// ����رհ�ť
	void onWindowShouldClose();

protected:
	virtual bool doMakeCurrent() = 0;
	virtual bool doSetTitle(const std::string& title) { return true; };
	virtual bool doSetSize(const GLWindowSize& size) { return true; };
	virtual bool doSetPosition(const GLWindowPos& pos) { return true; };
	virtual bool doSetSizeLimit(const GLWindowSize& minSize, const GLWindowSize& maxSize) { return true; };
	virtual void doSetVisible(bool visible) {};

private:
	static GLWindow* s_currentWindow;
	
	std::string _title;
	GLWindowSize _size;
	GLWindowSize _minSize;
	GLWindowSize _maxSize;
	GLWindowPos _pos;
	bool _shouldClose;
};

#endif // !_GL_OS_WINDOW_H_