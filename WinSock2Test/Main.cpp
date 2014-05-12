#pragma once
#include <conio.h>
#include "NicoNicoTools.h"

int main(void)
{
	using namespace std;
	using namespace NicoNicoTools;
	string tag = "Roosan";
	string user = "QBkpRLSYQYrVGUeAu8YAIuEa1sE";
	string tagsearchURL;
	vector<string> commentlist, movieidlist;
	map<string, vector<string>> allcommentlist;

	tagsearchURL = getTagSearchURL(tag);
	movieidlist = getMovieIDList(getSource(tagsearchURL));
	allcommentlist = idListToComments(movieidlist, user);
	showAllList(allcommentlist);

	/*
	cout << "UserID: " << user << endl;
	commentlist = getCommentList(user, getSource(commentURL));
	showList(commentlist);
	*/
	
	_getch(); // “K“–‚ÈƒL[“ü—Í‘Ò‚¿

	return 0;
}