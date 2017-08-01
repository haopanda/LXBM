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

	// �л���ǰ��Ⱦ����
	virtual bool makeCurrent() = 0;

	// �л�ǰ�󻺳���
	virtual void swapBuffers() = 0;

protected:
	int chooseFBConfig(const FBConfig& desired, const std::vector<FBConfig>& alternatives);
};

#endif // _GL_CONTEXT_H_