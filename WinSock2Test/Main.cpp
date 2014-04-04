#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <iostream>
#include <string>
#include <conio.h>
#include "RequestString.h"
#include "ConnectSocket.h"
#include "Util.h"

int main(void)
{
	RequestString rs("msg.nicovideo.jp/10/api/thread?version=20090904&thread=1173108780&res_from=-100");
	//RequestString rs("www.nicovideo.jp/tag/supercar?rss=2.0&sort=f");
	ConnectSocket cs;

	int sourcepos;
	std::string message;
	std::string source;
	std::string sourceSJIS;

	rs.setMethod("GET");
	rs.addHeader("Connection", "close");
	//rs.addHeader("Cookie", "user_session=user_session_16021410_fb9c5f7cc2176bbfbfa5f6536726c08046f6fb91294f7c6607015289d2618c5d");

	cs.foundConnection(rs.getHostStr());
	std::string rq = rs.makeCommand();
	message = cs.getMessage(rq);
	std::cout << rq << std::endl;

	sourcepos = message.find("\r\n\r\n") + 4;
	source = message.substr(sourcepos);
	
	sourceSJIS = UTF8ToSJIS(source.c_str());

	//std::cout << source.c_str() << std::endl;
	std::cout << sourceSJIS << std::endl;

	//showList(getMovieIDList(sourceSJIS));
	
	_getch(); // “K“–‚ÈƒL[“ü—Í‘Ò‚¿

	return 0;
}