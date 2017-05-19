CC = g++
CFLAGS = -g -std=c++17 -Wall -Wextra -pedantic
LDFLAGS = -g

all: main

main: main.o Array.hpp
	$(CC) $(LDFLAGS) main.o -o main.exe

main.o: main.cpp Array.hpp
	$(CC) $(CFLAGS) -c main.cpp

main: main.o Array.hpp
	$(CC) $(LDFLAGS) main.o -o main.exe

main.o: main.cpp Array.hpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm *.o *.exe
