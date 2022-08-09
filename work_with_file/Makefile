CC = gcc
CFLAGS = -c -Werror -Wall -Wextra

all: file_write reverse_read
file_write: file_write.o
	$(CC) file_write.o -o file_write
file_write.o: file_write.c
	$(CC) $(CFLAGS) file_write.c
reverse_read: reverse_read.o
	$(CC) reverse_read.o -o reverse_read
reverse_read.o: reverse_read.c
	$(CC) $(CFLAGS) reverse_read.c
clean:
	rm example.txt | rm *.o | rm reverse_read | rm file_write