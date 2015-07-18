#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <thread>
#include "Config.h"
#include "ChatInput.h"
#include "Receive.h"
#include "tjson.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;

int main(){

	TestJson();



	return 5;


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
		getchar();
		getchar();
        exit(1);
    }

    if(LOBYTE(wsaData.wVersion)!=2||HIBYTE(wsaData.wVersion)!=2){
        WSACleanup();
        cout<<"invaild version"<<endl;
		getchar();
		getchar();
        exit(1);
    }

	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == INVALID_SOCKET){
		WSACleanup();
		cout << "socket failed" << endl;
		getchar();
		getchar();
		exit(0);
	}



    saServer.sin_family=AF_INET;
    saServer.sin_port=htons(port);
    saServer.sin_addr.S_un.S_addr=inet_addr(host);

    ret=connect(sClient,(struct sockaddr *)&saServer,sizeof(saServer));
    if(ret==SOCKET_ERROR){
        cout<<"连接服务器失败!点击任意键退出....."<<endl;
        closesocket(sClient);
        WSACleanup();
		getchar();
        exit(1);
    }

	thread recThread(Receive, sClient);
	thread sendThread(ChatInput,sClient);
	recThread.join();
	sendThread.join();

	cout << "over" << endl;
    closesocket(sClient);
    WSACleanup();
	getchar();
	getchar();
	return 0;
}

