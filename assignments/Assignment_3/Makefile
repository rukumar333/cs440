CC = g++
CFLAGS = -g -std=c++14 -Wall -Wextra -pedantic
LDFLAGS = -g

all: test SharedPtr_test Array_test

test: test.o
	$(CC) $(LDFLAGS) test.o -o test.exe

test.o: test.cpp SharedPtr.hpp
	$(CC) $(CFLAGS) -c test.cpp

SharedPtr_test: SharedPtr_test.o
	$(CC) $(LDFLAGS) -pthread SharedPtr_test.o -o SharedPtr_test.exe

SharedPtr_test.o: SharedPtr_test.cpp SharedPtr.hpp
	$(CC) $(CFLAGS) -pthread -c SharedPtr_test.cpp

Array_test: Array_test.o MyInt.o
	$(CC) $(LDFLAGS) Array_test.o MyInt.o -o Array_test.exe

Array_test.o: Array_test.cpp Array.hpp
	$(CC) $(CFLAGS) -c Array_test.cpp

MyInt.o: MyInt.cpp
	$(CC) $(CFLAGS) -c MyInt.cpp

memcheck: SharedPtr_test
	valgrind ./SharedPtr_test.exe

clean:
	rm *.o *.exe
