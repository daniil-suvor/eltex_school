CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

all: client_tcp client_udp server
client_tcp.o: client_tcp.c
	$(CC) $(CFLAGS) client_tcp.c
client_tcp: client_tcp.o
	$(CC) client_tcp.o -o client_tcp

client_udp.o: client_udp.c
	$(CC) $(CFLAGS) client_udp.c
client_udp: client_udp.o
	$(CC) client_udp.o -o client_udp

server.o: server.c
	$(CC) $(CFLAGS) server.c
server: server.o
	$(CC) server.o -o server

clean:
	rm *.o | rm server client_tcp client_udp