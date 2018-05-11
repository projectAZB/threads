CC = gcc
CFLAGS = -pedantic -std=gnu99 -Wall
DEBUG_FLAGS = -g $(CFLAGS)
VALGRIND_FLAGS = valgrind --show-reachable=yes --leak-check=full

test_mythreads: main.c spin.h spin.c counter.h counter.c list.h list.c hash.h hash.c
	$(CC) $(DEBUG_FLAGS) spin.c counter.c list.c hash.c main.c -o test -lpthread -lm

test_pthreads: main.c spin.h spin.c counter.h counter.c list.h list.c hash.h hash.c
	$(CC) $(DEBUG_FLAGS) spin.c counter.c list.c hash.c main.c -o test_pthreads -lpthread -lm -DPTHREADS

valgrind: test
	$(VALGRIND_FLAGS) ./test

.PHONY: clean
clean:
	rm -rf *.dSYM test
