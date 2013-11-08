CC = gcc
DEBUG = -g -Wall -lcunit -I/usr/include/CUnit
header = uheap.h
sharedlib = libuheap.so
testcase_bin = testcase
objects = uheap.o
main: $(objects)
	$(CC) $(objects) --shared -o $(sharedlib)
	
clean:
	rm $(objects) $(testcase_bin) $(sharedlib)

install:
	cp $(sharedlib) /usr/lib/
	cp $(uheap.h) /usr/include/

test: uheap.o testcase.o
	$(CC) $(objects) testcase.o $(DEBUG) -o $(testcase_bin)
	./testcase

