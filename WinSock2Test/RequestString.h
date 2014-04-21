#include <string>
#include <map>
using namespace std;
#pragma once

class RequestString
{
private:
	string hoststr;
	string dirstr;
	string method;
	map <string, string> header;

public:
	RequestString();
	RequestString(string URL);
	~RequestString();

	void setURL(string URL);

	string getHostStr();
	string getDirStr();

	void setMethod(string method);
	void addHeader(string key, string value);

	string makeCommand();
};

