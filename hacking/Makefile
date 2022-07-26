CC = gcc
FLAGS = -no-pie -fno-stack-protector

all: main
main: main.c
	$(CC) $(FLAGS) main.c -o main
key: key.c
	$(CC) key.c -o key
	./key > key.txt
hack: main key
	./main < key.txt
clean:
	rm main | rm key | rm key.txt