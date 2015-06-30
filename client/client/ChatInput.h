
#ifndef CHAT_INPUT_H_
#define CHAT_INPUT_H_
#include <WinSock2.h>
#include <string>
#include <iostream>
#include "Config.h"

void ChatInput(SOCKET sockfd){
	using namespace std;
	char buf[MSGSIZE];
	cout << "直接输入消息，然后回车即可发送消息:";
	while (true){
		//cin >> buf;
		cin.getline(buf, MSGSIZE);
		int slen = send(sockfd, buf, strlen(buf),0);
		if (slen == SOCKET_ERROR){
			cout << "发送失败!" << endl;
			break;
		}else{
			//cout << "发送成功！" << endl;
		}
	}
}




#endif