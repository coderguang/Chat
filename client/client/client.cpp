#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "Config.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;
const int MAX = 20;
int main(){
    WORD mVersionRequested;
    WSADATA wsaData;//WSADATA�ṹ����������AfxSocketInit�������ص�WindowsSockets��ʼ����Ϣ��
    int ret;

    SOCKET sClient;
    struct sockaddr_in saServer;
    bool fSuccess=true;

    //winSock ��ʼ��

    mVersionRequested=MAKEWORD(2,2);//WinSock dll�İ汾

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
        cout<<"����ʧ��!"<<endl;
        closesocket(sClient);
        WSACleanup();
		getchar();
		getchar();
        exit(1);
    }

	char msg[] = "hello,�����Կͻ���";
	char buf[MAX];
	int i = 0;
	while (i++<10){		

		ret = send(sClient, (char*)&msg, sizeof(msg), 0);

		if (ret == SOCKET_ERROR){
			cout << "����ʧ��!" << endl;
			break;
		}

		int rev=recv(sClient, buf, MAX, 0);
		buf[rev] = '\0';
		if (rev > 0){
			cout << "�յ�����:" << buf << endl;
			cout.flush();
		}

	}
	cout << "over" << endl;
    closesocket(sClient);
    WSACleanup();
	getchar();
	getchar();
	return 0;
}
