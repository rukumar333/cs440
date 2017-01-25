CC = g++
CFLAGS = -g -O3 -std=c++14 -Wall -Wextra -pedantic -ldl
LDFLAGS = -g

test: test.o
	$(CC) $(LDFLAGS) test.o -o test

mytest: mytest.o
	$(CC) $(LDFLAGS) mytest.o -o mytest

# Deque.o: Deque.cpp
# 	$(CC) $(CFLAGS) -c Deque.cpp

test.o: test.cpp Deque.hpp
	$(CC) $(CFLAGS) -c test.cpp

mytest.o: mytest.cpp Deque.hpp
	$(CC) $(CFLAGS) -c mytest.cpp

clean:
	rm *.o mytest test
