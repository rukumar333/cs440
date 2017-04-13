CC = g++
CFLAGS = -g -std=c++14 -Wall -Wextra -pedantic
LDFLAGS = -g

test: test.o
	$(CC) $(LDFLAGS) test.o -o test.exe

test.o: test.cpp SharedPtr.hpp
	$(CC) $(CFLAGS) -c test.cpp

clean:
	rm *.o *.exe
