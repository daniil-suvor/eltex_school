CC=gcc
CFLAGS=-c -Wall -Wextra -Werror

all: my_vim
my_vim.o: my_vim.c my_vim.h
	$(CC) $(CFLAGS) my_vim.c
node.o: node.c
	$(CC) $(CFLAGS) node.c
my_vim: my_vim.o node.o
	$(CC) my_vim.o node.o -lncurses -o my_vim
clean:
	rm *.o | rm my_vim