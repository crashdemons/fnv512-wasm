CC=clang
CXX=clang++
CFLAGS=-I. -g -O0 -Wall -lstdc++

DEPS=fnv512.h

all: test

test: fnv512.o
	$(CXX) $(CFLAGS) -o test fnv512.o main.cpp

fnv512.o: fnv512.cpp fnv512.hpp uint512_llvm.hpp
	$(CXX) $(CFLAGS) fnv512.cpp -c


.PHONY: clean

clean:
	rm -f ./*.o
	rm -f test


