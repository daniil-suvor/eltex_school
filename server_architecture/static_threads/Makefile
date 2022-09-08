CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

all: client server
client.o: client.c
	$(CC) $(CFLAGS) client.c
client: client.o
	$(CC) client.o -o client

server.o: server.c
	$(CC) $(CFLAGS) server.c
server: server.o
	$(CC) server.o -o server -lpthread -lrt

clean:
	rm *.o | rm server client