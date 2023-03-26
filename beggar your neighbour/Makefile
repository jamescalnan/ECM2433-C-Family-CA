CC = gcc

all: single byn

single: single.o shuffle.o beggar.o
	$(CC) -o single single.o shuffle.o beggar.o -lgsl -lgslcblas -lm

byn: byn.o shuffle.o beggar.o
	$(CC) -o byn byn.o shuffle.o beggar.o -lgsl -lgslcblas -lm

single.o: single.c beggar.h
	$(CC) -c single.c

byn.o: byn.c beggar.h
	$(CC) -c byn.c

shuffle.o: shuffle.c shuffle.h
	$(CC) -c shuffle.c

beggar.o: beggar.c beggar.h
	$(CC) -c beggar.c

clean:
	rm -f single.o byn.o shuffle.o beggar.o single byn
