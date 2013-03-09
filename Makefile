CC = gcc
CFLAGS = -Wall -g

all: sudoku

sudoku.o: sudoku.c sudoku.h
	$(CC) $(CFLAGS) -c sudoku.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c


sudoku: sudoku.o util.o


clean:
	 rm -f *~ *.o sudoku core
