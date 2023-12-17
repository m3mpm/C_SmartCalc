.PHONY: build install uninstall clean lib test gcov_report

CC = gcc
# CFLAGS = -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname)
ifeq ($(OS),Darwin)
	CHECKFLAGS = -lcheck
else
	# CHECKFLAGS = -lcheck -lpthread -lrt -lm -lsubunit
	CHECKFLAGS = -lcheck -lpthread -lrt -lm
endif

build:
	mkdir ./build/; cd ./build/; qmake ../; make; mv C_SmartCalc.app SmartCalc.app

install: clean uninstall build
	mkdir $(HOME)/Desktop/C_SmartCalc/
	cp -rf ./build/SmartCalc.app $(HOME)/Desktop/C_SmartCalc/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/C_SmartCalc/

lib: 
	$(CC) $(CFLAGS) -c calc_logic.c -o calc_logic.o
	ar rc calc_logic.a calc_logic.o
	ranlib calc_logic.a

test: lib
	$(CC) $(CFLAGS) test.c calc_logic.a $(CHECKFLAGS) -o a.out
	./a.out

gcov_report: lib
	$(CC) $(CFLAGS) $(GCOVFLAGS) calc_logic.c test.c $(CHECKFLAGS) -o gcov_rep.out
	./gcov_rep.out
	lcov -t "gcov_rep" --output-file=coverag.info --capture --directory .
	genhtml -o ./report coverag.info

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out
	rm -rf ./report
	rm -rf ./build
