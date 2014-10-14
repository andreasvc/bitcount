tests: tests.out
	./tests.out

tests.out: bitcount.c bitcount.h tests.c
	gcc bitcount.c -Wall tests.c -o tests.out

clean:
	rm -f tests.out

.PHONY: tests clean
