#pragma once
#include "RequestString.h"
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <iostream>
#include <string>
#include <conio.h>


RequestString::RequestString()
{
}

RequestString::RequestString(std::string URL)
{
	setURL(URL);
}

RequestString::~RequestString()
{
}

void RequestString::setURL(std::string URL){
	int slashpos;
	slashpos = URL.find_first_of("/");
	hoststr = URL.substr(0, slashpos);
	dirstr = URL.substr(slashpos);

	addHeader("HOST", hoststr);
}

string RequestString::getHostStr(){
	return hoststr;
}
string RequestString::getDirStr(){
	return dirstr;
}

void RequestString::setMethod(std::string method){
	this->method = method;
}

void RequestString::addHeader(std::string key, std::string value){
	header[key] = value;
}

string RequestString::makeCommand(){
	std::string command;

	// HTTPでリクエストする文字列を生成
	command.append(method).append(" ").append(dirstr).append(" HTTP/1.1\r\n");
	for (auto itr = header.begin(); itr != header.end(); ++itr){
		command.append(itr->first).append(": ").append(itr->second).append("\r\n");
	}
	command.append("\r\n");

	return command;
}

/*
int main(int argc, char* argv[]){
	RequestString rs("brain.cc.kogakuin.ac.jp/~kanamaru/lecture/prog1/14-01.html");

	rs.setMethod("GET");
	rs.addHeader("HOST", rs.getHostStr());
	rs.addHeader("Connection", "close");

	std::cout << rs.makeCommand() << std::endl;

	_getch(); // 適当なキー入力待ち
	return 0;
}
*/