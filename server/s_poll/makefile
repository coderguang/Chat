server_poll : server.o SocketBase.o ../../../Common/include/json/json_value.o ../../../Common/include/json/json_reader.o ../../../Common/include/json/json_writer.o
	clang++ -Wall -g server.o SocketBase.o ../../../Common/include/json/json_value.o ../../../Common/include/json/json_reader.o ../../../Common/include/json/json_writer.o -o server_poll ../../../Common/lib/liblog.a ../../../Common/lib/libutil.a
server.o : server.cpp 
	clang++ -Wall -c -g server.cpp  
SocketBase.o : ../../../Common/net/socket/SocketBase.cpp 
	clang++ -Wall -c -g ../../../Common/net/socket/SocketBase.cpp ../../../Common/lib/liblog.a ../../../Common/lib/libutil.a
clean :
	-rm server_poll *.o *~
