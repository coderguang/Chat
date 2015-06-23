server : server.o
	g++ -g server.o -o server
server.o : server.cpp 
	g++ -c server.cpp ../../ComLib/linuxLib/linComNet.h
clean :
	rm *.o server
