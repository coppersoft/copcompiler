CC=gcc

all: copbuilder registers
	$(CC) copbuilder.o registers.o main.c
copbuilder:
	$(CC) -c copbuilder.c
registers:
	$(CC) -c registers.c
