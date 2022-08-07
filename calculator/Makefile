CC = gcc
CFLAGS = -c -Werror -Wextra -Wall
SHARED = -shared -lm
PLAGINS = sum difference product fraction

all: menu
plagins: libsum.so libdifference.so libfraction.so libproduct.so liblogorifm.so
libdifference.so: difference.c
	$(CC) $(CFLAGS) -fPIC difference.c
	gcc -o plagins/libdifference.so difference.o $(SHARED)
libproduct.so: product.c
	$(CC) $(CFLAGS) -fPIC product.c
	gcc -o plagins/libproduct.so product.o $(SHARED)
libfraction.so: fraction.c
	$(CC) $(CFLAGS) -fPIC fraction.c
	gcc -o plagins/libfraction.so fraction.o $(SHARED)
liblogorifm.so: logorifm.c
	$(CC) $(CFLAGS) -fPIC logorifm.c
	gcc -o plagins/liblogorifm.so logorifm.o $(SHARED)
libsum.so: sum.c
	$(CC) $(CFLAGS) -fPIC sum.c
	gcc -o plagins/libsum.so sum.o $(SHARED)
stack.o: stack.c
	$(CC) $(CFLAGS) stack.c
menu.o: menu.c
	$(CC) $(CFLAGS) menu.c
menu: plagins menu.o stack.o
	$(CC) stack.o menu.o -o menu -ldl
clean:
	rm *.o | rm plagins/*.so | rm menu