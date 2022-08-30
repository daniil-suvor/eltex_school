CC = gcc
CFLAGS = -c -Wextra -Werror -Wall

all: mqueue_example message_server client

client.o: client.c
	$(CC) $(CFLAGS) client.c
client: client.o
	$(CC) client.o -o client -lrt -pthread -lncurses

message_server.o: message_server.c
	$(CC) $(CFLAGS) message_server.c
message_server: message_server.o
	$(CC) message_server.o -o message_server -lrt

mqueue_example.o: mqueue_example.c
	$(CC) $(CFLAGS) mqueue_example.c
mqueue_example: mqueue_example.o
	$(CC) mqueue_example.o -o mqueue_example -lrt

clean:
	rm *.o | rm mqueue_example | rm client | rm message_server