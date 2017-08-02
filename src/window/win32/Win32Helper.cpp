#include "Win32Helper.h"
#include <windows.h>

const std::wstring& Win32Helper::convertUTF8ToWideString(const std::string& source)
{
	std::wstring str;
	int length = MultiByteToWideChar(CP_UTF8, 0, source.c_str(), -1, NULL, 0);

	if (length)
	{	
		WCHAR* target;
		target = (WCHAR*)calloc(length, sizeof(WCHAR));
		if (MultiByteToWideChar(CP_UTF8, 0, source.c_str(), -1, target, length))
		{
			str = target;
		}
		free(target);
	}

	return str;
}

const std::string& Win32Helper::convertWideStringToUTF8(const std::wstring& source)
{
	std::string str;

	int length = WideCharToMultiByte(CP_UTF8, 0, source.c_str(), -1, NULL, 0, NULL, NULL);
	if (length)
	{
		char* target = (char*)calloc(length, sizeof(char));
		if (WideCharToMultiByte(CP_UTF8, 0, source.c_str(), -1, target, length, NULL, NULL))
		{
			str = target;
		}
		free(target);
	}

	return str;
}