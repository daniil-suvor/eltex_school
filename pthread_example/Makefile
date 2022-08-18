CC = gcc
CFLAGS = -c -Wall -Werror -Wextra

all: main
main.o: pthread_ex.c
	$(CC) $(CFLAGS) pthread_ex.c
main: main.o
	$(CC) pthread_ex.o -o main -lpthread