# The compiler: g++ for C++ program
CC = g++

# compiler flags:
# -g 	add debugging information to the executable file
# -Wall	turns on most, but not all, compiler warnings
CFLAGS = -g -Wall
SOCKFLAGS = 
#SOCKFLAGS = -lnsl -lresolv -lsocket
# build all executable files
# They are:
# client from client.c
# server from server.c
all: client server

client: client.o
	$(CC) $(CFLAGS) $(SOCKFLAGS) -o client client.o
client.o: client.cpp
	$(CC) $(CFLAGS) -c client.cpp

server: server.o
	$(CC) $(CFLAGS) $(SOCKFLAGS) -o server server.o
server.o: server.cpp
	$(CC) $(CFLAGS) -c server.cpp

clean-mid:
	rm -f ./*.o

clean: clean-mid
	rm -f ./*~ ./client ./server