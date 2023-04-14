.PHONY: all clean test s21_graph.a s21_graph_algorithms check gcov_report
CC=g++ -std=c++17 -Wall -Werror -Wextra
OS := $(shell uname -s)
LFLAGS = -lgtest --coverage

ifeq ($(UNAME),Darwin)
	LEAKS := CK_FORK=no leaks --atExit -- ./test
	OPEN:= open
else
	LEAKS := valgrind --leak-check=full ./test
	OPEN:= xdg-open
endif

default: all

all: clean test

test: clean s21_graph_algorithms.a
	$(CC) test.cc s21_graph_algorithms.a -o test $(LFLAGS)
	./test --enable-coverage


s21_graph.a: s21_graph.o
	ar rcs s21_graph.a s21_graph.o
	ranlib $@
	cp $@ lib$@
	ranlib lib$@

s21_graph.o: s21_graph.hpp
	$(CC) -c -o s21_graph.o s21_graph.hpp

s21_graph_algorithms.a: s21_graph_algorithms.o
	ar rvs s21_graph_algorithms.a s21_graph_algorithms.o 
	ranlib $@
	cp $@ lib$@
	ranlib lib$@

s21_graph_algorithms.o: s21_graph_algorithms.hpp
	$(CC) -o s21_graph_algorithms.o s21_graph_algorithms.hpp

s21_navigator_interface:
	$(CC) main.cc s21_navigator_interface.hpp

clean:
	rm -rf test *.a *.o *.out *.cfg fizz *.gc* *.info report *.dSYM *.dot .clang-format

rebuild: clean all

linter:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cc *.hpp

leaks: test
	CK_FORK=no leaks --atExit -- ./test

valgrind: test
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./test

gcov_report: test
	lcov -c -d . -t test -o test.info
	genhtml -o report test.info
	open report/index.html
