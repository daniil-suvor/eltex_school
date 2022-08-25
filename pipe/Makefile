CC = gcc
CFLAGS = -c # -Werror -Wextra -Wall
TEST = test1 test2 test3 test4 test5

all: my_bash mkfifo_example pipe_example

mkfifo_example.o: mkfifo_example.c
	$(CC) $(CFLAGS) mkfifo_example.c
mkfifo_example: mkfifo_example.o
	$(CC) mkfifo_example.o -o mkfifo_example

pipe_example.o: pipe_example.c
	$(CC) $(CFLAGS) pipe_example.c
pipe_example: pipe_example.o
	$(CC) pipe_example.o -o pipe_example

my_bash.o: my_bash.c
	$(CC) $(CFLAGS) my_bash.c
my_bash: my_bash.o
	$(CC) my_bash.o -o my_bash

leak_cheack: my_bash
	@for i in $(TEST); do\
		valgrind --leak-check=full ./my_bash < $$i; \
		echo; \
	done
	
test: my_bash
	@for i in $(TEST); do\
		./my_bash < $$i > out_test; \
		(sh $$i) > out_ori; \
		diff out_ori out_test && echo "PASSED $$i!\n"; \
	done

clean:
	rm *.o | rm my_bash | rm pipe_example | rm mkfifo_example | rm out_ori out_test