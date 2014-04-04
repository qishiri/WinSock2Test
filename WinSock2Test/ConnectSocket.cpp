#include "ConnectSocket.h"
#include <string>
#include <winsock2.h>

ConnectSocket::ConnectSocket()
{
}


ConnectSocket::~ConnectSocket()
{
}

void ConnectSocket::foundConnection(std::string hoststr){
	WSADATA wsaData;
	struct sockaddr_in server;
	std::string filedest = "";
	unsigned int **addrptr;

	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
		printf("WSAStartup failed\n");
		exit(1);
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		printf("socket : %d\n", WSAGetLastError());
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(80); // HTTPのポートは80番です

	server.sin_addr.S_un.S_addr = inet_addr(hoststr.c_str());
	struct hostent *host;

	host = gethostbyname(hoststr.c_str());
	if (host == NULL) {
		if (WSAGetLastError() == WSAHOST_NOT_FOUND) {
			printf("host not found : %s\n", hoststr.c_str());
		}
		exit(1);
	}

	addrptr = (unsigned int **)host->h_addr_list;

	while (*addrptr != NULL) {
		server.sin_addr.S_un.S_addr = *(*addrptr);

		// connect()が成功したらloopを抜けます
		if (connect(sock,
			(struct sockaddr *)&server,
			sizeof(server)) == 0) {
			break;
		}

		addrptr++;
		// connectが失敗したら次のアドレスで試します
	}

	// connectが全て失敗した場合
	if (*addrptr == NULL) {
		printf("connect : %d\n", WSAGetLastError());
		exit(1);
	}

}

std::string ConnectSocket::getMessage(std::string command){
	char buf[128];
	std::string message;

	// HTTPリクエスト送信
	int n = send(sock, command.c_str(), command.length(), 0);
	if (n < 0) {
		printf("send : %d\n", WSAGetLastError());
		exit(1);
	}

	// サーバからのHTTPメッセージ受信
	while (n > 0) {
		memset(buf, 0, sizeof(buf));
		n = recv(sock, buf, sizeof(buf)-1, 0);
		if (n < 0) {
			printf("recv : %d\n", WSAGetLastError());
			exit(1);
		}

		// 受信結果を表示
		//		if (strcmp(buf, "Connection:")==0) puts("a"); chk = 1; continue;
		//		if (chk == 0) continue;
		message.append(buf);
	}
	closesocket(sock);
	WSACleanup();

	return message;
}