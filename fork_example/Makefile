CC = gcc
CFLAGS = -c -Werror -Wextra -Wall

all: out_pid exec_run my_bash my_calc
out_pid.o: out_pid.c
	$(CC) $(CFLAGS) out_pid.c
out_pid: out_pid.o
	$(CC) out_pid.o -o out_pid
example: example.c
	$(CC) example.c -o example
exec_run.o: exec_run.c
	$(CC) $(CFLAGS) exec_run.c
exec_run: example exec_run.o
	$(CC) exec_run.o -o exec_run
my_calc.o: my_calc.c
	$(CC) $(CFLAGS) my_calc.c
my_calc: my_calc.o
	$(CC) my_calc.o -o my_calc
my_bash.o: my_bash.c
	$(CC) $(CFLAGS) my_bash.c
my_bash: my_bash.o
	$(CC) my_bash.o -o my_bash
clean:
	rm *.o | rm out_pid | rm exec_run | rm example | rm my_bash | rm my_calc