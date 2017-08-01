#include "GLOSWindow.h"

GLOSWindow* GLOSWindow::s_currentWindow = nullptr;

bool GLOSWindow::makeCurrent()
{
	if (doMakeCurrent())
	{
		s_currentWindow = this;
		return true;
	}
	return false;
}

bool GLOSWindow::setTitle(const std::string& title)
{
	if (doSetTitle(title))
	{
		_title = title;
		return true;
	}
	return false;
}

bool GLOSWindow::setSize(const GLWindowSize& size)
{
	if (doSetSize(size))
	{
		_size = size;
		return true;
	}
	return false;
}

bool GLOSWindow::setPosition(const GLWindowPos& pos)
{
	if (doSetPosition(pos))
	{
		_pos = pos;
		return true;
	}
	return false;
}

bool GLOSWindow::setSizeLimit(const GLWindowSize& minSize, const GLWindowSize& maxSize)
{
	if (doSetSizeLimit(minSize, maxSize))
	{
		_minSize = minSize;
		_maxSize = maxSize;
		return true;
	}
	return false;
}

void GLOSWindow::onWindowShouldClose()
{
	_shouldClose = true;
}