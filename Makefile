CC=gcc

all: copbuilder
	$(CC) copbuilder.o main.c
copbuilder:
	$(CC) -c copbuilder.c