CC = gcc
CFLAGS = -c -Werror -Wextra -Wall
PLAGINS = sum difference product fraction

all: menu
plagins: libsum.so
libsum.so: sum.c
	$(CC) $(CFLAGS) -fPIC sum.c
	gcc -shared -o plagins/libsum.so sum.o
menu.o: menu.c
	$(CC) $(CFLAGS) menu.c -ldl
menu: plagins menu.o
	$(CC) menu.o -o menu
clean:
	rm *.o | rm *.so | rm menu