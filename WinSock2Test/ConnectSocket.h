#include <string>
#include <WinSock2.h>
#include "RequestString.h"
#pragma once

class ConnectSocket
{
private:
	SOCKET sock;

public:
	ConnectSocket();
	~ConnectSocket();

	void foundConnection(std::string hoststr);
	std::string getMessage(std::string command);
};

