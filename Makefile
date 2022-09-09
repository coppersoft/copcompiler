CC=gcc

all: copbuilder registers labels
	$(CC) copbuilder.o registers.o labels.o -g main.c -o copbuilder.exe
copbuilder:
	$(CC) -c -g copbuilder.c
registers:
	$(CC) -c -g registers.c
labels:
	$(CC) -c -g labels.c