CC = gcc
CFLAGS = -c -Wall -Werror -Wextra

all: modeling_shop
modeling_shop.o: modeling_shop.c
	$(CC) $(CFLAGS) modeling_shop.c
modeling_shop: modeling_shop.o
	$(CC) modeling_shop.o -o modeling_shop -lpthread
clean:
	rm *.o | rm modeling_shop | rm log