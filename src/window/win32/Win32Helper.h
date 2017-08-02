#ifndef _WIN32_HELPER_H_
#define _WIN32_HELPER_H_

#include <string>

class Win32Helper
{
public:
	// utf8×Ö·û´®×ª»¯³É¿í×Ö·û
	static const std::wstring& convertUTF8ToWideString(const std::string& source);

	// ¿í×Ö·û×ª»¯³Éutf8×Ö·û´®
	static const std::string& convertWideStringToUTF8(const std::wstring& source);
};

#endif // _WIN32_HELPER_H_
