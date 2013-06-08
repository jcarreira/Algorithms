.PHONY: clean depend

PROG     = test_rbt
CC      = gcc
CCFLAGS = -ansi -Wall 
CCFILES = $(wildcard *.c)
CCHEADS = $(wildcard *.h)
OFILES   = $(CCFILES:%.c=%.o)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

all: depend $(PROG)

$(PROG): $(OFILES)
	$(CC) $(CCFLAGS) $^ -o $@

test: $(PROG)
	./$(PROG)

depend: .makedeps

.makedeps: $(CCFILES) $(CCHEADS)
	$(CC) $(CCFLAGS) -MM $(CCFILES) > .makedeps
	
-include .makedeps	

clean:
	rm -f *.o .makedeps *~ $(PROG)
