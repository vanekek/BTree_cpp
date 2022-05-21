FLAGS = -fprofile-arcs -ftest-coverage
all: a.out

a.out: tests.o btree.o
	g++ $(FLAGS) btree.o tests.o -o a.out
tests.o: tests.cpp
	g++ $(FLAGS) -c tests.cpp -o tests.o
btree.o: btree.cpp
	g++ $(FLAGS) -c btree.cpp -o btree.o 
clean:
	rm -rf a.out tests btree *.o *.gcov *.gcda *.gcno 