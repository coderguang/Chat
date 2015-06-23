#include "../../ComLib/linuxLib/linComNet.h"
#include "Config.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
using namespace std;

int main(int argc,char **argv){
	int listenfd;
	int connfd;
	
	struct sockaddr_in cliaddr;
	struct sockaddr_in servaddr;
	
	listenfd=Socket(AF_INET,SOCK_STREAM,0);
	
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORT);
	//servaddr.sin_port=htons(atoi(argv[0]));
	servaddr.sin_addr.s_addr=INADDR_ANY;

	Bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	Listen(listenfd,10);
	
	while(true){
		socklen_t len=sizeof(cliaddr);

		connfd=accept(listenfd,(struct sockaddr *)&cliaddr,&len);
		
		if(connfd==ERROR){
			continue;
		}
		string ip=inet_ntoa(cliaddr.sin_addr);

		cout<<"ip="<<ip<<" connect!"<<endl;

	}
	






}
