#pragma once
#include <string>
#include <vector>
#include <map>

namespace NicoNicoTools
{
	using namespace std;
	string getTagSearchURL(string tag);
	string getSource(string URL);
	string getThreadID(string server_response);
	string getMessageServerNumber(string server_response);
	string movieIDToCommentURL(string movieID);
	vector<string> getMovieIDList(string server_response);
	vector<string> getCommentList(string user, string server_response);
	vector<string> getUniqueList(vector<string> list);
	map<string, vector<string>> idListToComments(vector<string> movieidlist, string user);
	void showList(vector<string> list);
	void showAllList(map<string, vector<string>> alllist);
}

