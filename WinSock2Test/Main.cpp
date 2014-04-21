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
#pragma once

int main(void)
{
	std::string tag = "Roosan";
	std::string tagsearchURL = "www.nicovideo.jp/tag/" + UrlEncode(SJISToUTF8(tag.c_str())) + "?rss=2.0&sort=v";
	RequestString thread_id;
	ConnectSocket cs;
	NicoNicoTools nt;

	std::string user = "QBkpRLSYQYrVGUeAu8YAIuEa1sE";
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
	
	_getch(); // “K“–‚ÈƒL[“ü—Í‘Ò‚¿

	return 0;
}