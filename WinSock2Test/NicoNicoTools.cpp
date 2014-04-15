#include "NicoNicoTools.h"
#include <iostream>
#include <algorithm>
#include <string>
#include "RequestString.h"
#include "ConnectSocket.h"
#include "Util.h"

NicoNicoTools::NicoNicoTools()
{
}

NicoNicoTools::~NicoNicoTools()
{
}

std::vector<std::string> NicoNicoTools::getMovieIDList(std::string server_response)
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

std::vector<std::string> NicoNicoTools::getUniqueList(std::vector<std::string> list)
{
	std::sort(list.begin(), list.end());
	std::vector<std::string>::iterator new_end = std::unique(list.begin(), list.end());
	list.erase(new_end, list.end());

	return list;
}



void NicoNicoTools::showList(std::vector<std::string> list)
{
	std::vector<std::string>::iterator it = list.begin();  // イテレータのインスタンス化
	while (it != list.end())  // 末尾要素まで
	{
		std::cout << *it << std::endl;  // *演算子で間接参照
		++it;                 // イテレータを１つ進める
	}
}

/*
map<std::string, vector<std::string>> getCommentList(std::string user, vector<std::string> movieIDlist)
{
map<std::string, vector<std::string>> commentlist;
int userchk, idpos, idlength;
int commentchk, commentpos, commentlength;
std::string id, comment;
while (1){
userchk = buf.find(user);
if (userchk == std::string::npos)
break;
commentpos = userchk + 52;
buf = buf.substr(commentpos);
commentlength = buf.find_first_of("<");
comment = buf.substr(0, idlength);


}
return list;
}
*/


std::vector<std::string> NicoNicoTools::getCommentList(std::string user, std::string server_response)
{
	std::vector<std::string> list;
	int userchk = 0;
	int commentpos = 0, commentlength;
	std::string comment;
	std::string buf = server_response;
	while (1){
		userchk = buf.find(user, commentpos);
		if (userchk == std::string::npos)
			break;
		commentpos = buf.find(">", userchk) + 1;
		commentlength = buf.find_first_of("<", commentpos) - commentpos;
		comment = buf.substr(commentpos, commentlength);
		list.push_back(comment);
	}
	return list;
}

std::string NicoNicoTools::getThreadID(std::string server_response)
{
	std::string threadid;
	int idchk, idpos, idlength;
	idchk = server_response.find("thread_id");
	if (idchk == std::string::npos)
		return 0;
	idpos = idchk + 10;
	idlength = server_response.find_first_of("&", idpos) - idpos;
	threadid = server_response.substr(idpos, idlength);

	return threadid;
}

std::string NicoNicoTools::movieIDToThreadID(string movieID)
{
	std::string threadid;
	RequestString rs;
	ConnectSocket cs;

	std::string geturl = "flapi.nicovideo.jp/api/getflv?v=" + movieID;
	rs.setURL(geturl);

	std::string sourceSJIS;
	sourceSJIS = getSource(geturl);

	threadid = getThreadID(sourceSJIS);
	
	return threadid;
}

std::string NicoNicoTools::getSource(string URL){
	RequestString rs(URL);
	ConnectSocket cs;

	std::string message, source, sourceSJIS;
	int sourcepos;

	rs.setMethod("GET");
	rs.addHeader("Connection", "close");
	rs.addHeader("Cookie", "user_session=user_session_16021410_fb9c5f7cc2176bbfbfa5f6536726c08046f6fb91294f7c6607015289d2618c5d");

	cs.foundConnection(rs.getHostStr());
	std::string rq = rs.makeCommand();
	message = cs.getMessage(rq);
	//std::cout << rq << std::endl;

	sourcepos = message.find("\r\n\r\n") + 4;
	source = message.substr(sourcepos);

	sourceSJIS = UTF8ToSJIS(source.c_str());

	return sourceSJIS;
}

std::map<string, vector<string>> NicoNicoTools::idListToComments(vector<string> movieidlist, std::string user)
{
	std::map<string, vector<std::string>> allcommentlist;
	std::vector<string> commentlist;
	std::vector<std::string>::iterator it = movieidlist.begin();  // イテレータのインスタンス化

	std::string threadid;
	std::string commenturl;
	std::string source;
	int count = 0;
	while (it != movieidlist.end())
	{
		std::cout << ++count << std::endl;
		commenturl = "";
		std::cout << *it << std::endl;  // *演算子で間接参照
		threadid = movieIDToThreadID(*it);
		commenturl.append("msg.nicovideo.jp/10/api/thread?version=20090904&thread=").append(threadid).append("&res_from=-100");
		source = getSource(commenturl);
		commentlist = getCommentList(user, source);

		allcommentlist[*it] = commentlist;
		++it;
		Sleep(1500);
	}
	std::cout << "end" << std::endl;

	return allcommentlist;
}

void NicoNicoTools::showAllList(map<string, vector<string>> alllist)
{
	std::map<string, vector<string>> allcommentlist;
	std::vector<string> commentlist;
	std::vector<std::string>::iterator it;

	for (auto itr = allcommentlist.begin(); itr != allcommentlist.end(); ++itr){
		std::cout << itr->first << std::endl;
		while (it != allcommentlist[itr->first].end())
		{
			std::cout << *it << std::endl;
			++it;
		}
	}
}