#ifndef RECEIVE_H_
#define RECEIVE_H_
#include <iostream>
#include <WinSock2.h>
#include "Config.h"
#include <Windows.h>
<<<<<<< HEAD
#include "json/json.h"
=======
#include <string>
#include "jsonPP/include/json/json.h"
>>>>>>> 12a518ee8db0997d4cac799296e4b84b4d002b22
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
<<<<<<< HEAD
			Json::Value js;
			Json::Reader reader;
			if (!reader.parse(str, js)){
				cout << "json read str fail" << endl;
			}
			cout << "id=" << js["id"].asInt() << "   name=" << js["name"].asString() << "  age=" << js["age"].asInt() << endl;
			//cout << "公共频道:" << buf << endl;
=======
			string str=new string(buf);
			Json::Value js;
			js.parse(str);
			cout<<"id="<<js["id"].asInt()<<" ,name="<<js["name"].asString()<<" ,age="<<js["age"].asInt()<<endl;
			cout << "公共频道:" << buf << endl;
>>>>>>> 12a518ee8db0997d4cac799296e4b84b4d002b22
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		}
	}
}


#endif
