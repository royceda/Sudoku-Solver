CC=gcc
CFLAGS=-std=c99 -Wall -g -O0
LDFLAGS=
EXEC=sudoku


all: $(EXEC)

sudoku: sudoku.o verification.o lecture.o remplissage.o ecritureCNF.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf sudoku		
