#pragma once
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctype.h>
#include <cctype>
#include <string>

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

//! %XXのXXをchar型にして返します。
char hexToChar(char first, char second)
{
	int digit;

	digit = (first >= 'A' ? ((first & 0xDF) - 'A') + 10 : (first - '0'));
	digit *= 16;
	digit += (second >= 'A' ? ((second & 0xDF) - 'A') + 10 : (second - '0'));
	return static_cast< char >(digit);
}

//! 改行コードか判定します。
bool isLF(const std::string            & str,
	const std::string::size_type & length,
	std::string::size_type       & index,
	char                         * tmpStr)
{
	if (tmpStr[0] != '0')
		return false;

	tmpStr[1] = toupper(tmpStr[1]);
	if (tmpStr[1] == 'A')
	{
		// [0A]は改行コード
		return true;
	}

	if (tmpStr[1] == 'D')
	{
		// [0D]も改行コード
		if ((index + 3) < length && str[index + 1] == '%')
		{
			// [0D]の後に[%0A]がある時は、[%0A]の後までインデックスを進めます。
			tmpStr[0] = str[index + 2];
			tmpStr[1] = str[index + 3];

			if (tmpStr[0] == '0' &&
				(tmpStr[1] == 'A' || tmpStr[1] == 'a'))
			{
				index += 3;
			}
		}
		return true;
	}

	return false;
}

/**
URLデコードをした文字列を返します。
改行コード(0x0A, 0x0D)は'\n'にします。
**/
std::string urlDecode(const std::string & str)
{
	std::string retStr;
	char tmpStr[2];
	std::string::size_type length = str.size();

	for (std::string::size_type i = 0; i < length; i++)
	{
		if (str[i] == '+')
		{
			// [+]は半角スペース
			retStr += ' ';
		}
		else if (str[i] == '%' && (i + 2) < length)
		{
			tmpStr[0] = str[i + 1];
			tmpStr[1] = str[i + 2];

			if (std::isxdigit(tmpStr[0]) && std::isxdigit(tmpStr[1]))
			{
				i += 2;

				// 改行コードのチェック
				if (isLF(str, length, i, tmpStr))
				{
					retStr += "<br>";
				}
				else
				{
					retStr += hexToChar(tmpStr[0], tmpStr[1]);
				}
			}
			else
			{
				// no digit
				retStr += '%';
			}
		}
		else
		{
			retStr += str[i];
		}
	}
	return retStr;
}
