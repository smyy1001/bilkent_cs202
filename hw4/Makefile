# Makefile to compile the source code

CC=g++

CFLAGS=-c -Wall

all: hw

hw: avlTree.o main.o
	$(CC) avlTree.cpp main.cpp -o avlfreq


avlTree.o: avlTree.cpp
	$(CC) $(CFLAGS) avlTree.cpp



main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp


clean:
	rm *o avlfreq