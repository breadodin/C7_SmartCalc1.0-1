CFLAGS = -Wall -Werror -Wextra -std=c11 -g
OS := $(shell uname -s)
MYFLAGS = -lcheck -lsubunit -pthread -lrt -lm

ifeq ($(OS),Linux)
	CFLAGS+=-D LINUX
else
	ifeq ($(OS),Darwin)
		CFLAGS+=-D MAC
	endif
endif

all: clean test gcov_report

dvi:
	open ../README.md

install: clean uninstall
	mkdir build
	cd build && qmake ../Qt/Calculator && make
	rm -rf build

dist: install
	tar -czf calc.tar.gz ~/SmartCalc/Calculator
	rm -rf ~/SmartCalc

uninstall:
	rm -rf ~/SmartCalc

vpath %.c core:core/tests/ test

test: s21_SmartCalc.c s21_input_check.c s21_parser.c s21_sort.c test.c
	mkdir -p test_files
	gcc $^ -o test_files/$@ $(CFLAGS) $(MYFLAGS) --coverage

gcov_report: test
	./test_files/test
	gcovr --html-details test_files/gcov_result.html
	open test_files/gcov_result.html

check:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i core/*.c
	clang-format -i core/tests/*.c
	clang-format -i core/*.h
	clang-format -i Qt/Calculator/*.cpp
	clang-format -i Qt/Calculator/*.h

clean:
	rm -rf *.o *.gcda *.a *.html *.gcno *.css .clang-format build 
	rm -f test
	rm -rf *.tar.gz
	rm -rf Qt/Calculator/*.o
	rm -rf test_files

rebuild: clean all
