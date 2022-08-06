CC = gcc
CFLAGS = -c -Werror -Wextra -Wall

all: menu
sum.o: sum.c
	$(CC) $(CFLAGS) -fPIC sum.c
difference.o: difference.c
	$(CC) $(CFLAGS) -fPIC difference.c
product.o: product.c
	$(CC) $(CFLAGS) -fPIC product.c
fraction.o: fraction.c
	$(CC) $(CFLAGS) -fPIC fraction.c
libcalculator.so: sum.o difference.o product.o fraction.o
	gcc -shared -o libcalculator.so sum.o difference.o product.o fraction.o
run: menu
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD ./menu
menu.o: menu.c
	$(CC) $(CFLAGS) menu.c
menu: menu.o libcalculator.so
	$(CC) menu.o -o menu -L. -lcalculator
clean:
	rm *.o | rm *.so | rm menu