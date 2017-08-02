#include "GLWindow.h"

GLWindow* GLWindow::s_currentWindow = nullptr;

bool GLWindow::makeCurrent()
{
	if (doMakeCurrent())
	{
		s_currentWindow = this;
		return true;
	}
	return false;
}

bool GLWindow::setTitle(const std::string& title)
{
	if (doSetTitle(title))
	{
		_title = title;
		return true;
	}
	return false;
}

bool GLWindow::setSize(const GLWindowSize& size)
{
	if (doSetSize(size))
	{
		_size = size;
		return true;
	}
	return false;
}

bool GLWindow::setPosition(const GLWindowPos& pos)
{
	if (doSetPosition(pos))
	{
		_pos = pos;
		return true;
	}
	return false;
}

bool GLWindow::setSizeLimit(const GLWindowSize& minSize, const GLWindowSize& maxSize)
{
	if (doSetSizeLimit(minSize, maxSize))
	{
		_minSize = minSize;
		_maxSize = maxSize;
		return true;
	}
	return false;
}

void GLWindow::setVisible(bool visible)
{
	doSetVisible(visible);
}

void GLWindow::onWindowShouldClose()
{
	_shouldClose = true;
}