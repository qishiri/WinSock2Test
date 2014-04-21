#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <iostream>
#include <string>
#include <conio.h>
#include "RequestString.h"
#include "ConnectSocket.h"
#include "NicoNicoTools.h"
#include "Util.h"

int main(void)
{
	std::string tag = "Roosan";
	std::string tagsearchURL = getTagSearchURL(tag);
	std::string user = "QBkpRLSYQYrVGUeAu8YAIuEa1sE";
	NicoNicoTools nt;

	std::vector<std::string> commentlist, movieidlist;
	std::map<string, vector<string>> allcommentlist;

	movieidlist = nt.getMovieIDList(nt.getSource(tagsearchURL));

	allcommentlist = nt.idListToComments(movieidlist, user);

	nt.showAllList(allcommentlist);
	/*
	std::cout << "UserID: " << user << std::endl;
	commentlist = nt.getCommentList(user, nt.getSource(commentURL));
	nt.showList(commentlist);
	*/
	
	_getch(); // 適当なキー入力待ち

	return 0;
}