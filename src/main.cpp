#include "window/WindowManager.h"
#include "glad/glad.h"

#include <windows.h>

int APIENTRY wWinMain(HINSTANCE hInstance,
	                 HINSTANCE hPrevInstance,
					 LPTSTR    lpCmdLine,
					 int       nCmdShow)
{
	auto wm = WindowManager::getInstance();
	auto window = wm->createWindow();

	window->setVisible(true);
	glClearColor(1.0f, 1.0f, 0.0f, 1.f);

	bool running = true;
	while (running)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		window->makeCurrent();

		running = window->windowShouldClose();

		wm->waitEvents();
	}

	wm->destroyInstance();

	return 0;
}