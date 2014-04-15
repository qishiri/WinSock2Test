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
	
	vector<string> getMovieIDList(std::string server_response);
	vector<string> getUniqueList(vector<string> list);
	void showList(vector<string> list);
	vector<string> getCommentList(string user, string server_response);
	string getThreadID(string server_response);
	string getMessageServerURL(std::string server_response);
	string movieIDToCommentURL(string movieID);
	string getSource(string URL);
	map<string, vector<string>> idListToComments(vector<string> movieidlist, std::string user);
	void showAllList(map < string, vector<string>> alllist);
};

