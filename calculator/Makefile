CC = gcc
CFLAGS = -c -Werror -Wextra -Wall

all: menu
sum.o: sum.c
	$(CC) $(CFLAGS) sum.c
difference.o: difference.c
	$(CC) $(CFLAGS) difference.c
product.o: product.c
	$(CC) $(CFLAGS) product.c
fraction.o: fraction.c
	$(CC) $(CFLAGS) fraction.c
libcalculator.a: sum.o difference.o product.o fraction.o
	ar rc libcalculator.a sum.o difference.o product.o fraction.o
menu.o: menu.c
	$(CC) $(CFLAGS) menu.c
menu: menu.o libcalculator.a
	$(CC) menu.o -o menu -L. -lcalculator
clean:
	rm *.o | rm *.a | rm menu