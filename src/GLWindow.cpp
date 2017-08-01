#include "GLWindow.h"
#include <new>

GLWindow* GLWindow::create(int width, int height, const char* title, GLWindow* share)
{
	auto pRet = new (std::nothrow) GLWindow();
	if (pRet)
	{
		return pRet->init(width, height, title, share);
	}
	return nullptr;
}

GLWindow* GLWindow::init(int width, int height, const char* title, GLWindow* share)
{
	//
}