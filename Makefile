CC=gcc

all: copbuilder registers
	$(CC) -g copbuilder.o registers.o main.c -o main
copbuilder:
	$(CC) -g -c copbuilder.c
registers:
	$(CC) -g -c registers.c
