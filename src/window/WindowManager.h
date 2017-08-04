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

	// ���������Ѿ����¼������еĴ����¼�����������
	void pollEvents();

	// �����߳̽���˯��״̬��ֱ���¼�������������һ���¼�
	// Ȼ������Щ�¼�������.
	void waitEvents();

protected:
	WindowManager(void);

	// ����ƽ̨�ض�ʵ������ƽ̨����ļ��ж���
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