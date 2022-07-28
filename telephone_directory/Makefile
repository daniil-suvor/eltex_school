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
	./main < my_test_1
	./main < my_test_2
check_leack: main
	valgrind --leak-check=full -s ./main < my_test_1 > out
	valgrind --leak-check=full -s ./main < my_test_2 > out
	rm out
clean:
	rm *.o
	rm main