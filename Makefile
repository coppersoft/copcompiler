CC=gcc

all: copbuilder
	$(CC) copbuilder.o main.c -o main.exe
copbuilder:
	$(CC) -c copbuilder.c