# Makefile to compile the source code

CC=g++

CFLAGS=-c -Wall

all: hw1

hw1: main.o sorting.o
	$(CC) main.o sorting.o -o 22103640_hw1


main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp



sorting.o: sorting.cpp
	$(CC) $(CFLAGS) sorting.cpp


clean:
	rm *o 22103640_hw1