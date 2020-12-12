CC = gcc -Wall -m64  # code is compiled for 64 bit x86

all: test-with-handin test-with-handout code-handin.s

test-with-handin: code-handin.o test.c
	$(CC) -c test.c -o test.o
	$(CC) test.o code-handin.o -o test-with-handin

test-with-handout: test.c
	$(CC) -c test.c -o test.o
	$(CC) test.o code-unopt.o -o test-with-handout

#
# do not use this target if you are a student.  Just run make
#
#
handout: code-unopt.s code-opt.s code-opt.o code-unopt.o hw2.pdf
	tar cvf hw2.tar code-unopt.s code-unopt.o code-opt.s code-opt.o code.h test.c code-handin.c Makefile hw2.pdf

code-handin.s code-handin.o: code-handin.c
	$(CC) -c code-handin.c -o code-handin.o
	$(CC) -S code-handin.c -o code-handin.s


code-unopt.s code-unopt.o : code.c
	$(CC) -c code.c -o code-unopt.o
	$(CC) -S code.c -o code-unopt.s

code-opt.s  code-opt.o : code.c
	$(CC) -O -c code.c -o code-opt.o
	$(CC) -O -S code.c -o code-opt.s

clean:
	rm -f test-with-handout test-with-handin
