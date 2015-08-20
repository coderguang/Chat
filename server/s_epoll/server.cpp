#include "../../../Common/net/socket/SocketBase.h"
#include "config.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

using namespace std;
using namespace GCommon::GNet::GSocket;

static const int MAX_CONN=1200;
static struct epoll_event *events;

int main(int argc,char **argv){

	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;

	int fdmax;
	int listener;
	int newfd;

	char buf[1024];

	int nbytes;
	socklen_t addrlen;
	int yes;
	int epfd=-1;
	int res=-1;
	struct epoll_event ev;
	int index=0;
	int client_fd=-1;

	listener=CSocketBase::Socket(AF_INET,SOCK_STREAM,0);
	
	if(setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int))==-1){
		std::cout<<"setsocketopt faild!"<<std::endl;	
		exit(0);
	}

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=INADDR_ANY;
	serveraddr.sin_port=htons(PORT);

	memset(&(serveraddr.sin_zero),'\0',8);
	
	CSocketBase::Bind(listener,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

	CSocketBase::Listen(listener,10);

	fdmax=listener;
	
	events=(epoll_event*)calloc(MAX_CONN,sizeof(struct epoll_event));

	if((epfd=CSocketBase::Epoll_create(MAX_CONN))==-1){
		std::cout<<"epoll create faildi!"<<std::endl;
		exit(1);
	}

	ev.events=EPOLLIN;
	ev.data.fd=fdmax;

	if(CSocketBase::CSocketBase::Epoll_ctl(epfd,EPOLL_CTL_ADD,fdmax,&ev)<0){
		std::cout<<"CSocketBase::Epoll_ctl failed"<<std::endl;
		exit(1);
	}
	
	for(;;){
		res=CSocketBase::Epoll_wait(epfd,events,MAX_CONN,-1);
		for(index=0;index<res;index++){

			client_fd=events[index].data.fd;//get the first events

			if(client_fd==listener){//new connections
				addrlen=sizeof(clientaddr);
				newfd=CSocketBase::Accept(listener,(struct sockaddr *)&clientaddr,&addrlen);
				if(-1!=newfd){
					ev.events=EPOLLIN;
					ev.data.fd=newfd;
					if(CSocketBase::Epoll_ctl(epfd,EPOLL_CTL_ADD,newfd,&ev)<0){
						std::cout<<"CSocketBase::Epoll_ctl faild when add new sockfd"<<std::endl;
						exit(1);
					}else{
						std::cout<<"CSocketBase::Epoll_ctl add socket "<<newfd<<std::endl;
					}
				
				}
				continue;
			
			}else{


				if(events[index].events&EPOLLHUP){
					if(CSocketBase::Epoll_ctl(epfd,EPOLL_CTL_DEL,client_fd,&ev)<0){
						std::cout<<"del the socket="<<client_fd<<std::endl;
					}else{
						std::cout<<"socket"<<client_fd<<"disconnec..."<<std::endl;
					}
					close(client_fd);
					continue;
				}



				if(events[index].events&EPOLLIN){
					memset(buf,'\0',sizeof(buf));
					if((nbytes=CSocketBase::Recv(client_fd,buf,sizeof(buf),0))<=0){
						if(nbytes==0){
							std::cout<<"socket "<<client_fd<<" is hung up"<<std::endl;
						}else{
							std::cout<<"recv error in socket"<<client_fd<<std::endl;
								
							/*	
							if(CSocketBase::Epoll_ctl(epfd,CSocketBase::Epoll_ctl_DEL,client_fd,&ev)<0){
								std::cout<<"CSocketBase::Epoll_ctl del error,socket="<<client_fd<<std::endl;
							} 
							Close(client_fd);
							*/
						}
					}else{
						std::cout<<"get msg="<<buf<<endl;
						/*
						if(send(client_fd,buf,nbytes,0)==-1){
							std::cout<<"send error,socket="<<client_fd<<std::endl;
						}*/
					}
							
				}
			}


		
		}
	
	
	}


	std::cout<<"over"<<std::endl;

	return 0;
	


}
