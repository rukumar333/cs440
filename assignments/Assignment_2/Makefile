CC = g++
CFLAGS = -g -std=c++14 -Wall -Wextra -pedantic
LDFLAGS = -g

test: test.o
	$(CC) $(LDFLAGS) test.o -o test.exe

test.o: test.cpp Map.hpp
	$(CC) $(CFLAGS) -c test.cpp

stress_test: stress_test.o
	$(CC) $(LDFLAGS) stress_test.o -o stress_test.exe

stress_test.o: stress_test.cpp Map.hpp
	$(CC) $(CFLAGS) -c stress_test.cpp

gdb: stress_test
	gdb -x gdb_commands.txt ./stress_test.exe

clean:
	rm *.o *.exe *.data
