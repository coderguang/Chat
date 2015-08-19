server : server.o SocketBase.o
	clang++ -Wall -g server.o SocketBase.o -o server -ljson -lpthread ../../../Common/lib/liblog.a ../../../Common/lib/libutil.a
server.o : server.cpp 
	clang++ -Wall -c -g server.cpp ../../../Common/net/socket/SocketBase.cpp -ljson -lpthread ../../../Common/lib/liblog.a ../../../Common/lib/libutil.a
SocketBase.o : ../../../Common/net/socket/SocketBase.cpp 
	clang++ -Wall -c -g ../../../Common/net/socket/SocketBase.cpp -ljson -lpthread  ../../../Common/lib/liblog.a ../../../Common/lib/libutil.a
clean :
	rm server *.o *~
