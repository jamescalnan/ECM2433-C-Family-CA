CC = gcc

all: single byn

single: single.o shuffle.o
	$(CC) -o single single.o shuffle.o -lgsl -lgslcblas -lm

byn: byn.o shuffle.o
	$(CC) -o byn byn.o shuffle.o -lgsl -lgslcblas -lm

single.o: single.c
	$(CC) -c single.c

byn.o: byn.c
	$(CC) -c byn.c

shuffle.o: shuffle.c shuffle.h
	$(CC) -c shuffle.c

clean:
	rm -f single.o byn.o shuffle.o single byn