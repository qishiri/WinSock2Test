#include <Windows.h>
#include <vector>
#include <algorithm>
#include <iostream>
#pragma once

std::string UTF8ToSJIS(const char* utf8) {

	size_t size = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, nullptr, 0);
	WCHAR* ws = new WCHAR[size];
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, ws, size);

	size = WideCharToMultiByte(CP_ACP, 0, ws, -1, nullptr, 0, 0, 0);
	char* s = new char[size];
	WideCharToMultiByte(CP_ACP, 0, ws, -1, s, size, 0, 0);

	std::string res(s);

	delete(ws);
	delete(s);

	return std::move(res);
}

std::string SJISToUTF8(const char* sjis) {

	size_t size = MultiByteToWideChar(CP_ACP, 0, sjis, -1, nullptr, 0);
	WCHAR* ws = new WCHAR[size];
	MultiByteToWideChar(CP_ACP, 0, sjis, -1, ws, size);

	size = WideCharToMultiByte(CP_UTF8, 0, ws, -1, nullptr, 0, 0, 0);
	char* s = new char[size];
	WideCharToMultiByte(CP_UTF8, 0, ws, -1, s, size, 0, 0);

	std::string res(s);

	delete(ws);
	delete(s);

	return std::move(res);
}

std::string UrlEncode(const std::string & str)
{
	std::string retStr;

	std::string::size_type length = str.size();
	for (std::string::size_type i = 0; i < length; i++)
	{
		if (('0' <= str[i] && str[i] <= '9') ||
			('a' <= str[i] && str[i] <= 'z') ||
			('A' <= str[i] && str[i] <= 'Z') ||
			str[i] == '-' || str[i] == '.' ||
			str[i] == '_' || str[i] == '~')
		{
			// 数字/アルファベット/[-][.][_][~]はそのまま  
			retStr += str[i];
		}
		else
		{
			retStr += '%';
			char tmp[3];
			_snprintf_s(tmp, 3, "%X", static_cast< unsigned char >(str[i]));
			retStr += tmp;
		}
	}

	return retStr;
}