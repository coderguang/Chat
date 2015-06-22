#ifndef COM_NET_H_
#define COM_NET_H_

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h> 

/**
 *This is the common net header file.
 *Use for socket.
 *
 * Author:coderguang
 * Date:2015/06/22
 *
 */

const int OK=0;
const int ERROR=-1;

int Socket(int family,int type,int protocol){
	int temp=socket(family,type,protocol);
	if(ERROR==temp){
		std::cout<<"socket init failed!"<<std::endl;
		return ERROR;
	}
	return temp;
}

int Connect(int sockfd,const struct sockaddr *servaddr,socklen_t addrlen){
	int temp=connect(sockfd,servaddr,addrlen);
	if(ERROR==temp){
		std::cout<<"connect failed!"<<std::endl;
		return ERROR;
	}
	return OK;

}

int Bind(int sockfd,const struct sockaddr *myaddr,socklen_t len){
	int temp=bind(sockfd,myaddr,len);
	if(ERROR==temp){
		std::cout<<"bind failed!"<<std::endl;
		return ERROR;
	}
	return OK;
}

int Listen(int sockfd,int backlog){
	int temp=listen(sockfd,backlog);
	if(ERROR==temp){
		std::cout<<"listen failed!"<<std::endl;
		return ERROR;
	}
	return OK;
}

int Accept(int sockfd,struct sockaddr *cliaddr,socklen_t *addrlen){
	int temp=accept(sockfd,cliaddr,addrlen);
	if(ERROR==temp){
		std::cout<<"accept failed!"<<std::endl;
		return ERROR;
	}
	return OK;

	
}


#endif
