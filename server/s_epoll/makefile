server : server.o SocketBase.o
	clang++ -Wall -g server.o SocketBase.o -o server -ljson ../../../Common/lib/liblog.a ../../../Common/lib/libutil.a
server.o : server.cpp 
	clang++ -Wall -c -g server.cpp -ljson 
SocketBase.o : ../../../Common/net/socket/SocketBase.cpp 
	clang++ -Wall -c -g ../../../Common/net/socket/SocketBase.cpp ../../../Common/lib/liblog.a ../../../Common/lib/libutil.a
clean :
	rm server *.o *~
