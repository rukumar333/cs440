CC = g++
CFLAGS = -g -O3 -std=c++14 -Wall -Wextra -pedantic
LDFLAGS = -g

test: test.o
	$(CC) $(LDFLAGS) test.o -o test.exe

test.o: test.cpp Map.hpp
	$(CC) $(CFLAGS) -c test.cpp

clean:
	rm *.o *.exe
