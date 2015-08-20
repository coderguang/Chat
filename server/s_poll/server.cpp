#include "../../../Common/net/socket/SocketBase.h"
#include "../../../Common/json/json.h"
#include "config.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;
using namespace GCommon::GNet::GSocket;

static const int OPEN_MAX=128;

int main(int argc,char **argv){

	Json::Value obj;
	obj["id"]=1001;
	obj["name"]="guang";
	obj["age"]=23;

	Json::FastWriter fastWriter;
	string sstr=fastWriter.write(obj);

	int i,maxfd,sockfd,listenfd,connfd;
	int nready;
	ssize_t n;
	struct pollfd client[OPEN_MAX];
	char buf[MSGSIZE];
	socklen_t clilen;
	
	struct sockaddr_in cliaddr;
	struct sockaddr_in servaddr;
	
	listenfd=CSocketBase::Socket(AF_INET,SOCK_STREAM,0);
	
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORT);
	//servaddr.sin_port=htons(atoi(argv[0]));
	servaddr.sin_addr.s_addr=INADDR_ANY;

	CSocketBase::Bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	CSocketBase::Listen(listenfd,10);
	
	client[0].fd=listenfd;
	client[0].events=POLLRDNORM;

	for(i=1;i<OPEN_MAX;i++){
		client[i].fd=-1;
	}
	
	maxfd=0; //initialize

	struct timeval t;
	t.tv_sec=2;
	t.tv_usec=10;


	for(;;){
		nready=CSocketBase::Poll(client,maxfd+1,1000);
	
		if(client[0].revents&POLLRDNORM){//new client connecton
			clilen=sizeof(cliaddr);
			connfd=CSocketBase::Accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);

			for(i=1;i<OPEN_MAX;i++){
				if(client[i].fd<0){
					cout<<"socket="<<connfd<<" connected!"<<endl;
					client[i].fd=connfd;//save the new sockfd
					client[i].events=POLLRDNORM;
					break;
				}
			}
			if(i==OPEN_MAX){
				cout<<"sockfd set full!"<<endl;
			}

			if(connfd>maxfd){
				maxfd=connfd;//for select
			}
			if(nready<=0){
				continue; //no more readable
			}

	
		}
		
		for(i=1;i<maxfd;i++){//check all clients for data
			if((sockfd=client[i].fd)<0){
				continue;
			}
			if(client[i].revents&POLLRDNORM){
				memset(buf,sizeof(buf),'\0');
				if((n=CSocketBase::Read(sockfd,buf,MSGSIZE))==0){//connections close by client
					cout<<"socket="<<sockfd<<" is disconnect..."<<endl;
					CSocketBase::Close(sockfd);//connection closed by client
					client[i].fd=-1;
				}else if(n>0){
					buf[n]='\0';
					cout<<"get the msg:"<<buf<<endl;
					for(int j=1;j<maxfd;j++){
						if(client[j].fd!=-1){
							//Writen(client[j].fd,sstr.c_str(),strlen(sstr.c_str()));
							
						}
					}
					
				}else if(n<0){
					if(errno==ECONNRESET){
						cout<<"socket="<<sockfd<<" is reset..."<<endl;
						CSocketBase::Close(sockfd);//connection reset by client
						client[i].fd=-1;
					}
				}
				if(nready<=0){
					break;
				}
			
			}
		}
	}
}
