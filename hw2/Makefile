# Makefile to compile the source code

CC=g++

CFLAGS=-c -Wall

all: hw

hw: hw2.o NgramTree.o
	$(CC) hw2.o NgramTree.o -o 22103640_hw2


hw2.o: hw2.cpp
	$(CC) $(CFLAGS) hw2.cpp



NgramTree.o: NgramTree.cpp
	$(CC) $(CFLAGS) NgramTree.cpp


clean:
	rm *o 22103640_hw2