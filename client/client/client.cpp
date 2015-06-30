#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "Config.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;
const int MAX = 128;

class proto{
public:
	char name[10];
	char msg[20];
	proto(string n, string m){
		memcpy(name, n.c_str(), n.length() + 1);
		memcpy(msg, m.c_str(), m.length() + 1);
	}
};

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

	char msg[] = "hello,I'm from client";
	char sbuf[MAX];
	char rbuf[MAX];
	string str;
	proto *tmp = new proto("", "");
	int i = 0;
	while (true){		

		int rev = recv(sClient, rbuf, MAX, 0);
		rbuf[rev] = '\0';

		//int rev = recv(sClient, (char*)tmp, MAX, 0);
		if (rev > 0){
			cout << "�յ�����:" << rbuf << endl;
			//cout << "�յ�����:name=" <<tmp->name<<" ,msg="<<tmp->msg  << endl;
		}

		cout << "��������������:";
		//cin.getline(sbuf, MAX);
		//cin >> str;
		cin >> sbuf;
		int len = strlen(sbuf);
		ret = send(sClient,sbuf, strlen(sbuf), 0);

		if (ret == SOCKET_ERROR){
			cout << "����ʧ��!" << endl;
			break;
		}

	}

	cout << "over" << endl;
    closesocket(sClient);
    WSACleanup();
	getchar();
	getchar();
	return 0;
}

