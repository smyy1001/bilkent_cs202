# Makefile to compile the source code

CC=g++

CFLAGS=-c -Wall

all: hw

hw: heap.o heapsort.o
	$(CC) heap.cpp heapsort.cpp -o heapsort


heap.o: heap.cpp
	$(CC) $(CFLAGS) heap.cpp



heapsort.o: heapsort.cpp
	$(CC) $(CFLAGS) heapsort.cpp


clean:
	rm *o heapsort