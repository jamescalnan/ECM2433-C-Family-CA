CC = gcc
CFLAGS = -Wall

all: piglatin test_pig

piglatin: piglatin.c pig.c pig.h
	$(CC) $(CFLAGS) -o piglatin piglatin.c pig.c

test_pig: test_pig.c pig.c pig.h
	$(CC) $(CFLAGS) -o test_pig test_pig.c pig.c

clean:
	rm -f piglatin test_pig
