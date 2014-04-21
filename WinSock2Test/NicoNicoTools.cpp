#pragma once
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

string getTagSearchURL(string tag){
	std::string tagsearchURL;
	tagsearchURL = "www.nicovideo.jp/tag/" + UrlEncode(SJISToUTF8(tag.c_str())) + "?rss=2.0&sort=v";

	return tagsearchURL;
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

std::string NicoNicoTools::getMessageServerURL(std::string server_response)
{
	std::string url;
	int urlchk, urlpos, urllength;
	urlchk = server_response.find("ms=");
	if (urlchk == std::string::npos)
		return 0;
	urlpos = urlchk + 35;
	urllength = server_response.find_first_of("%", urlpos) - urlpos;
	url = server_response.substr(urlpos, urllength);

	return url;
}

std::string NicoNicoTools::movieIDToCommentURL(string movieID)
{
	std::string threadid, msgserver, commenturl;
	RequestString rs;

	std::string geturl = "flapi.nicovideo.jp/api/getflv?v=" + movieID;
	rs.setURL(geturl);

	std::string sourceSJIS;
	sourceSJIS = getSource(geturl);

	threadid = getThreadID(sourceSJIS);
	msgserver = getMessageServerURL(sourceSJIS);
	commenturl.append("msg.nicovideo.jp/").append(msgserver).append("/api/thread?version=20090904&thread=").append(threadid).append("&res_from=-1000");

	return commenturl;
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

std::vector<std::string> NicoNicoTools::getUniqueList(std::vector<std::string> list)
{
	std::sort(list.begin(), list.end());
	std::vector<std::string>::iterator new_end = std::unique(list.begin(), list.end());
	list.erase(new_end, list.end());

	return list;
}

std::map<string, vector<string>> NicoNicoTools::idListToComments(vector<string> movieidlist, std::string user)
{
	std::map<string, vector<std::string>> allcommentlist;
	std::vector<string> commentlist;
	std::vector<std::string>::iterator it = movieidlist.begin();  // �C�e���[�^�̃C���X�^���X��

	std::string commenturl;
	std::string source;
	int count = 0;
	while (it != movieidlist.end())
	{
		std::cout << ++count << "/" << movieidlist.size() << std::endl;
		//std::cout << *it << std::endl;  // *���Z�q�ŊԐڎQ��
		commenturl = movieIDToCommentURL(*it);
		source = getSource(commenturl);
		commentlist = getCommentList(user, source);

		allcommentlist[*it] = commentlist;
		++it;
		Sleep(5500);
	}

	return allcommentlist;
}

void NicoNicoTools::showList(std::vector<std::string> list)
{
	std::vector<std::string>::iterator it = list.begin();  // �C�e���[�^�̃C���X�^���X��
	while (it != list.end())  // �����v�f�܂�
	{
		std::cout << *it << std::endl;  // *���Z�q�ŊԐڎQ��
		++it;                 // �C�e���[�^���P�i�߂�
	}
}

void NicoNicoTools::showAllList(map<string, vector<string>> alllist)
{
	std::vector<string> commentlist;
	for (auto itr = alllist.begin(); itr != alllist.end(); ++itr){
		std::vector<std::string>::iterator it = alllist[itr->first].begin();  // �C�e���[�^�̃C���X�^���X��
		if (it != alllist[itr->first].end()){
			std::cout << itr->first << std::endl;
			while (it != alllist[itr->first].end())
			{
				std::cout << *it << std::endl;
				++it;
			}
			std::cout << std::endl;
		}
	}
}