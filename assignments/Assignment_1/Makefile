CC = g++
CFLAGS = -g -O3 -std=c++14 -Wall -Wextra -pedantic
LDFLAGS = -g

test: test.o
	$(CC) $(LDFLAGS) test.o -o class_test -ldl

mytest: mytest.o
	$(CC) $(LDFLAGS) mytest.o -o mytest

sort: sort.o
	$(CC) $(LDFLAGS) sort.o -o sort -ldl

test.o: test.cpp Deque.hpp
	$(CC) $(CFLAGS) -c test.cpp -ldl

mytest.o: mytest.cpp Deque.hpp
	$(CC) $(CFLAGS) -c mytest.cpp

clean:
	rm *.o mytest test
