#include "WindowManager.h"

WindowManager* WindowManager::s_instance = nullptr;

WindowManager* WindowManager::getInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = createNativeInstance();
		if (s_instance == nullptr)
		{
			// todo
		}
	}
	return s_instance;
}

void WindowManager::destroyInstance()
{
	if (s_instance == nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

WindowManager::WindowManager(void)
{
	// todo
}

WindowManager::~WindowManager()
{
	for (auto itor = _windows.begin(); itor != _windows.end(); ++itor)
	{
		delete (*itor);
	}
	_windows.clear();
}

bool WindowManager::init()
{
	return true;
}

GLWindow* WindowManager::createWindow()
{
	GLWindow* window = doCreateWindow();
	if (window)
	{
		_windows.push_back(window);
	}
	return window;
}

void WindowManager::pollEvents()
{
	doPollEvents();
}

void WindowManager::waitEvents()
{
	doWaitEvents();
}