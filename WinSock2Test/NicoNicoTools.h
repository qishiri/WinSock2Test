#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;

class NicoNicoTools
{
public:
	NicoNicoTools();
	~NicoNicoTools();

	string getSource(string URL);
	string getThreadID(string server_response);
	string getMessageServerURL(std::string server_response);
	string movieIDToCommentURL(string movieID);
	vector<string> getMovieIDList(std::string server_response);
	vector<string> getCommentList(string user, string server_response);
	vector<string> getUniqueList(vector<string> list);
	map<string, vector<string>> idListToComments(vector<string> movieidlist, std::string user);
	void showList(vector<string> list);
	void showAllList(map < string, vector<string>> alllist);
};

