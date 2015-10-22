CC = gcc

CFLAGS = -g -Wall $(INCLUDES)

LDFLAGS = -g

hashmap-test: hashmap-test.o hashmap.o

hashmap-test.o: hashmap-test.c hashmap.h

hashmap.o: hashmap.c hashmap.h

.PHONY: clean
clean:
	rm -f *.o core hashmap-test

.PHONY: all
all: clean main

