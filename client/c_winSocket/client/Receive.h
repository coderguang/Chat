#ifndef RECEIVE_H_
#define RECEIVE_H_
#include <iostream>
#include <WinSock2.h>
#include "Config.h"
#include <Windows.h>
#include <string>
#include "jsonPP/include/json/json.h"
using namespace std;
void Receive(SOCKET sockfd){
	char buf[MSGSIZE];
	//cout << "开始接收消息:" << endl;	
	while (true){
		int rev = recv(sockfd, buf, 128, 0);
		buf[rev] = '\0';
		string str(buf);
		if (rev > 0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);

			string str(buf);
			cout << "get the server msg:" << str << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		}
	}
}


#endif
