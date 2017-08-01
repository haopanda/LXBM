#ifndef _GL_CONTEXT_H_
#define _GL_CONTEXT_H_

#include <vector>

struct FBConfig
{
	int redBits;
	int greenBits;
	int blueBits;
	int alphaBits;
	int depthBits;
	int stencilBits;
	int accumRedBits;
	int accumGreenBits;
	int accumBlueBits;
	int accumAlphaBits;
	int auxBuffers;
	bool stereo;
	int samples;
	bool sRGB;
	bool doubleBuffer;
	int handle;
};

class GLContext
{
public:
	static GLContext* create();

	// 切换当前渲染环境
	virtual bool makeCurrent() = 0;

	// 切换前后缓冲区
	virtual void swapBuffers() = 0;

protected:
	int chooseFBConfig(const FBConfig& desired, const std::vector<FBConfig>& alternatives);
};

#endif // _GL_CONTEXT_H_