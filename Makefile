CC=g++
CFLAGS=-I.

all: library test

library: fnv512.o
	$(CC) -o fnv512.o fnv512.cpp -c

test: fnv512.o
	$(CC) -o test fnv512.o main.cpp


.PHONY: clean

clean:
	rm -f ./*.o
	rm -f test


