#ifndef _WIN32_HELPER_H_
#define _WIN32_HELPER_H_

#include <string>

class Win32Helper
{
public:
	// utf8�ַ���ת���ɿ��ַ�
	static const std::wstring& convertUTF8ToWideString(const std::string& source);

	// ���ַ�ת����utf8�ַ���
	static const std::string& convertWideStringToUTF8(const std::wstring& source);
};

#endif // _WIN32_HELPER_H_
