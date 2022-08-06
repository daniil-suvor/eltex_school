CC = gcc
CFLAGS = -c -Werror -Wextra -Wall
PLAGINS = sum difference product fraction

all: menu
plagins: libsum.so libdifference.so libfraction.so libproduct.so
libdifference.so: difference.c
	$(CC) $(CFLAGS) -fPIC difference.c
	gcc -shared -o plagins/libdifference.so difference.o
libproduct.so: product.c
	$(CC) $(CFLAGS) -fPIC product.c
	gcc -shared -o plagins/libproduct.so product.o
libfraction.so: fraction.c
	$(CC) $(CFLAGS) -fPIC fraction.c
	gcc -shared -o plagins/libfraction.so fraction.o
libsum.so: sum.c
	$(CC) $(CFLAGS) -fPIC sum.c
	gcc -shared -o plagins/libsum.so sum.o
stack.o: stack.c
	$(CC) $(CFLAGS) stack.c
menu.o: menu.c
	$(CC) $(CFLAGS) menu.c
menu: plagins menu.o stack.o
	$(CC) stack.o menu.o -o menu -ldl
clean:
	rm *.o | rm plagins/*.so | rm menu