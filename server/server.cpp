#include "../../ComLib/linuxLib/linComNet.h"
#include "../../ComLib/linuxLib/Func.h"
#include "../../ComLib/json/json.h"
#include "config.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
using namespace std;

class proto{
public:
	char name[10];
	char msg[20];
	proto(string n,string m){
		memcpy(name,n.c_str(),n.length()+1);
		memcpy(msg,m.c_str(),m.length()+1);
	}
};




int main(int argc,char **argv){

	Json::Value obj;
	obj["id"]=1001;
	obj["name"]="guang";
	obj["age"]=23;

	Json::FastWriter fastWriter;
	string sstr=fastWriter.write(obj);

	int i,counter,maxfd,sockfd,listenfd,connfd;
	int nready,client[FD_SETSIZE];
	ssize_t n;
	fd_set rset,allset;
	char buf[MSGSIZE];
	socklen_t clilen;
	
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
	
	maxfd=listenfd; //initialize
	counter=-1;

	for(i=0;i<FD_SETSIZE;i++){
		client[i]=-1;
	}
	
	FD_ZERO(&allset);
	FD_SET(listenfd,&allset);

	for(;;){
		rset=allset;
		nready=Select(maxfd+1,&rset,NULL,NULL,NULL);
	
		if(FD_ISSET(listenfd,&rset)){//new client connecton
			clilen=sizeof(cliaddr);
			connfd=Accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);

			for(i=0;i<FD_SETSIZE;i++){
				if(client[i]<0){
					cout<<"socket="<<connfd<<" connected!"<<endl;
					client[i]=connfd;//save the new sockfd
					break;
				}
			}
			if(i==FD_SETSIZE){
				cout<<"sockfd set full!"<<endl;
			}
			FD_SET(connfd,&allset);//add new to set
			if(connfd>maxfd){
				maxfd=connfd;//for select
			}
			if(i>counter){//max index in client[]
				counter=i;
			}
			if(nready<=0){
				continue; //no more readable
			}

	
		}
		
		for(i=0;i<FD_SETSIZE;i++){//check all clients for data
			if((sockfd=client[i])<0){
				continue;
			}
			if(FD_ISSET(sockfd,&rset)){
				memset(buf,sizeof(buf),'\0');
				if((n=Read(sockfd,buf,MSGSIZE))==0){
					cout<<"socket="<<sockfd<<" is disconnect..."<<endl;
					close(sockfd);//connection closed by client
					FD_CLR(sockfd,&allset);
					client[i]=-1;
				}else{
					buf[n]='\0';
					cout<<"get the msg:"<<buf<<endl;
					for(int j=0;j<FD_SETSIZE;j++){
						if(client[j]!=-1){
							//Writen(client[j],buf,n);
							//Writen(client[j],sstr.c_str(),sizeof(sstr.c_str()));
							Writen(client[j],sstr.c_str(),strlen(sstr.c_str()));
							
						}
					}
					
				}
				if(nready<=0){
					break;
				}
			
			}
		}
	}
}
