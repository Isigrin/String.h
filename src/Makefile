FLAGS1 = -std=c11 -D_GNU_SOURCE -Wall -Wextra -Werror
.PHONY: all clean rebuild test string.a gcov_report check

UNAME := $(shell uname)
GCOV = -fprofile-arcs -ftest-coverage
FLAGS2 = -lcheck

ifeq ($(UNAME),Darwin)
    FLAGS2 = -lcheck
endif
ifeq ($(UNAME),Linux)
    FLAGS2 = -lcheck -lcheck_pic -lpthread -lrt -lm -lsubunit
endif

default: all

all: clean string.a test

string.o: string.c sprintf.c
	gcc $(FLAGS1) -c string.c sprintf.c

string.a: string.o sprintf.o
	ar rcs string.a string.o sprintf.o
	ranlib string.a
	cp string.a libstring.a

test: string.a
	gcc $(FLAGS1) test.c libstring.a -o Test $(FLAGS2)
	./Test

gcov_report: test.c string.a
	gcc $(GCOV) test.c $(FLAGS2) string.c sprintf.c -o Test
	./Test
	lcov -t "string" -o Test.info -c -d .
	genhtml -o report Test.info

clean:
	rm -rf *.o *.a Test *.cfg fizz *.gc* *.info report

rebuild:
	$(MAKE) clean
	$(MAKE) all

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.h *.c
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	CK_FORK=no leaks --atExit -- ./Test