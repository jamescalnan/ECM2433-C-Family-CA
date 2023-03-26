CC = gcc
CFLAGS = -Wall

all: demo_shuffle quality

demo_shuffle: demo_shuffle.c riffle.c riffle.h
	$(CC) $(CFLAGS) -o demo_shuffle demo_shuffle.c riffle.c

quality: quality.c riffle.c riffle.h
	$(CC) $(CFLAGS) -o quality quality.c riffle.c

clean:
	rm -f demo_shuffle quality
