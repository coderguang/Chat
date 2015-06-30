

#ifndef RECEIVE_H_
#define RECEIVE_H_
#include <iostream>
#include <WinSock2.h>
#include "Config.h"
#include <Windows.h>
using namespace std;
void Receive(SOCKET sockfd){
	char buf[MSGSIZE];
	//cout << "开始接收消息:" << endl;	
	while (true){
		int rev = recv(sockfd, buf, 128, 0);
		buf[rev] = '\0';
		if (rev > 0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			cout << "公共频道:" << buf << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		}
	}
}


#endif