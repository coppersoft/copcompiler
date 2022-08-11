CC=gcc

all: copbuilder registers labels
	$(CC) copbuilder.o registers.o labels.o main.c
copbuilder:
	$(CC) -c copbuilder.c
registers:
	$(CC) -c registers.c
labels:
	$(CC) -c labels.c