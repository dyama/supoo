
PROGRAM=supoo
OBJS=supoo.o value.o list.o hash.o dump.o parse.o func.o arena.o

CC=gcc
CFLAGS=-Wall -g -lm -O0 -std=c99
# CFLAGS=-Wall -lm -O3 -std=c99

.PHONY: clean
.SUFFIXES: .c .o

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM) test.lisp

debug: $(PROGRAM)
	cgdb $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.gch *~ $(PROGRAM) $(OBJS) 2>/dev/null

