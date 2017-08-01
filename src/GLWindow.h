#ifndef _GL_WINDOW_H_
#define _GL_WINDOW_H_

class GLWindow
{
public :
	virtual ~GLWindow(void);

	static GLWindow* create(int width, int height, const char* title, GLWindow* share);
	static GLWindow* getCurrentContext();
	static bool init();
	static void terminate();

	void destroy();

	int shouldClose();
	void setShouldClose(int value);

	void setTitle(const char* title);
	void setIcon();//todo
	
	void getPos();// todo
	void setPos(int posX, int posY);

	void getSize(); // todo
	void setSize(int width, int height);
	void setSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight);

	void setAspectRatio(int number, int denom);

	void getFrameBufferSize();//todo
	void getFrameSize(); // todo

	void iconify();// todo
	void restore();// todo
	void maximize();// todo

	void show();
	void hide();

	void requestFocus();// todo

	void getInputMode();// todo
	void setInputMode(int mode, int value);// todo

	int getKey(int key);// todo
	int getMouseButton();
	int getCursorPos(); // todo

	void setCursor();// todo

	void makeContextCurrent();
	void swapBuffers();

protected:
	GLWindow(void);

	GLWindow* init(int width, int height, const char* title, GLWindow* share);
};

#endif // !_GL_WINDOW_H_