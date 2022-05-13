CC=g++
CFLAGS= -Wall -g -fprofile-arcs -ftest-coverage
all: tests
tests.o: tests.cpp
	${CC} -c tests.cpp -o tests.o ${CFLAGS}
btree.o: btree.cpp
	${CC} -c btree.cpp -o btree.o ${CFLAGS}
tests: tests.o btree.o
	${CC} btree.o tests.o -o tests ${CFLAGS}
clean:
	@rm -rf *.o *.gcno *.gcda *.gcov tests 2&>/dev/null