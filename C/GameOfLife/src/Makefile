IDIR =../include
CC = gcc
CFLAGS = -I$(IDIR)

ODIR = obj
LDIR = ../lib

LIBS = -lm

_DEPS = matrix.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ_main = matrix.o gameoflife.o
OBJ_main = $(patsubst %,$(ODIR)/%,$(_OBJ_main))

_OBJ_tests = matrix.o tests.o
OBJ_tests = $(patsubst %,$(ODIR)/%,$(_OBJ_tests))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: gameoflife tests

gameoflife: $(OBJ_main)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

tests: $(OBJ_tests)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

check:
	./tests

install:
	mv gameoflife ~/local/bin

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~