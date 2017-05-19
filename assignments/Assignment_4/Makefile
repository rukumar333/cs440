CC = g++
CFLAGS = -g -std=c++17 -Wall -Wextra -pedantic
LDFLAGS = -g

all: main test_Array smaller_test

main: main.o Array.hpp
	$(CC) $(LDFLAGS) main.o -o main.exe

main.o: main.cpp Array.hpp
	$(CC) $(CFLAGS) -c main.cpp

test_Array: test_Array.o Array.hpp
	$(CC) $(LDFLAGS) test_Array.o -o test_Array.exe

test_Array.o: test_Array.cpp Array.hpp
	$(CC) $(CFLAGS) -c test_Array.cpp

smaller_test: smaller_test.o Array.hpp
	$(CC) $(LDFLAGS) smaller_test.o -o smaller_test.exe

smaller_test.o: smaller_test.cpp Array.hpp
	$(CC) $(CFLAGS) -c smaller_test.cpp

clean:
	rm *.o *.exe
