#include <Windows.h>
#include <vector>
#include <algorithm>

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


std::vector<std::string> getMovieIDList(std::string server_response)
{
	std::vector<std::string> list;
	std::string buf = server_response;
	int idchk, idpos, idlength;
	while (1){
		idchk = buf.find("<link>http://www.nicovideo.jp/watch/");
		if (idchk == std::string::npos)
			break;
		idpos = idchk + 36;
		buf = buf.substr(idpos);
		idlength = buf.find_first_of("<");
		list.push_back(buf.substr(0, idlength));
	}
	return list;
}

std::vector<std::string> getUniqueList(std::vector<std::string> list)
{
	std::sort(list.begin(), list.end());
	std::vector<string>::iterator new_end = std::unique(list.begin(), list.end());
	list.erase(new_end, list.end());
	
	return list;
}

void showList(std::vector<std::string> list)
{
	int count = 0;
	vector<std::string>::iterator it = list.begin();  // イテレータのインスタンス化
	while (it != list.end())  // 末尾要素まで
	{
		cout << *it << endl;  // *演算子で間接参照
		++it;                 // イテレータを１つ進める
	}
}