
PROGRAM=supoo
OBJS=supoo.o value.o ary.o float.o symbol.o dump.o

CC=gcc
CFLAGS=-Wall -g -lm

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

