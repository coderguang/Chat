#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "Config.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;

int main(){
    WORD mVersionRequested;
    WSADATA wsaData;//WSADATA结构被用来保存AfxSocketInit函数返回的WindowsSockets初始化信息。
    int ret;

    SOCKET sClient;
    struct sockaddr_in saServer;
    bool fSuccess=true;

    //winSock 初始化

    mVersionRequested=MAKEWORD(2,2);//WinSock dll的版本

    ret=WSAStartup(mVersionRequested,&wsaData);

    if(ret!=0){
        cout<<"WSASartup  failed!"<<endl;
        exit(1);
    }

    if(LOBYTE(wsaData.wVersion)!=2||HIBYTE(wsaData.wVersion)!=2){
        WSACleanup();
        cout<<"invaild version"<<endl;
        exit(1);
    }

	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == INVALID_SOCKET){
		WSACleanup();
		cout << "socket failed" << endl;
		exit(0);
	}



    saServer.sin_family=AF_INET;
    saServer.sin_port=htons(port);
    saServer.sin_addr.S_un.S_addr=inet_addr(host);

    ret=connect(sClient,(struct sockaddr *)&saServer,sizeof(saServer));
    if(ret==SOCKET_ERROR){
        cout<<"连接失败!"<<endl;
        closesocket(sClient);
        WSACleanup();
        exit(1);
    }

	while (true){
		char msg[] = "hello,I'm from client";

		ret = send(sClient, (char*)&msg, sizeof(msg), 0);

		if (ret == SOCKET_ERROR){
			cout << "发送失败!" << endl;
			break;
		}
	}
    closesocket(sClient);
    WSACleanup();
    return 0;
}

