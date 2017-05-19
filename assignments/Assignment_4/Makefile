CC = g++
CFLAGS = -g -std=c++17 -Wall -Wextra -pedantic
LDFLAGS = -g

all: main

main: main.o Array.hpp
	$(CC) $(LDFLAGS) main.o -o main.exe

main.o: main.cpp Array.hpp
	$(CC) $(CFLAGS) -c main.cpp

test_Array: test_Array.o Array.hpp
	$(CC) $(LDFLAGS) test_Array.o -o test_Array.exe

test_Array.o: test_Array.cpp Array.hpp
	$(CC) $(CFLAGS) -c test_Array.cpp

clean:
	rm *.o *.exe
