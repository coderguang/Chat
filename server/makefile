server : server.o
	g++ -g server.o -o server
server.o : server.cpp 
	g++ -c server.cpp ../../ComLib/ComNet.h
clean :
	rm *.o server
