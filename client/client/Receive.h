

#ifndef RECEIVE_H_
#define RECEIVE_H_
#include <iostream>
#include <WinSock2.h>
#include "Config.h"
using namespace std;
void Receive(SOCKET sockfd){
	char buf[MSGSIZE];
	cout << "��ʼ������Ϣ:" << endl;
	while (true){
		int rev = recv(sockfd, buf, 128, 0);
		buf[rev] = '\0';
		if (rev > 0){
			cout << "�յ�������Ϣ:" << buf << endl;
		}
	}
}


#endif