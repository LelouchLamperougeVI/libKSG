CC=gcc
CFLAGS=-lm -lgsl -O3 -Wall
DEPS=ksg.h
SDIR=src
_SRC=ksg.c kdtree.c unique.c
SRC = $(patsubst %,$(SDIR)/%,$(_SRC))

libksg.so: $(SRC)
	$(CC) -shared -fPIC -o $@ $^ $(CFLAGS)

test: $(SDIR)/test.c $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)
