CC = g++
CFLAGS = -g -std=c++14 -O3 -Wall -Wextra -pedantic
LDFLAGS = -g

test: test.o
	$(CC) $(LDFLAGS) test.o -o test.exe

test.o: test.cpp Map.hpp
	$(CC) $(CFLAGS) -c test.cpp

gdb: test
	gdb -x gdb_commands.txt ./test.exe

clean:
	rm *.o *.exe
