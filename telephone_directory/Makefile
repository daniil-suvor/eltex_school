CC=gcc
CFLAGS=-c -Wall -Wextra -Werror

all: main
menu.o: menu.c menu.h
	$(CC) $(CFLAGS) menu.c
telephone_directory.o: telephone_directory.c telephone_directory.h
	$(CC) $(CFLAGS) telephone_directory.c
main: telephone_directory.o menu.o
	$(CC) telephone_directory.o menu.o -o main
test: main
	./main < my_test && echo "RASSED"
clean:
	rm *.o
	rm main