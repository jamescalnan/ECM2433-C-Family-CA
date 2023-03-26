#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "beggar.c"
#include "shuffle.h" // Add this line


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s Nplayers\n", argv[0]);
        exit(1);
    }

    int Nplayers = atoi(argv[1]);
    int deck[52];
    for (int i = 0; i < 52; i++) {
        deck[i] = i % 13 + 2;
    }

    shuffle(deck, 52, time(NULL)); // Add this line

    int turns = beggar(Nplayers, deck, 1);
    printf("\nGame finished in %d turns.\n", turns);
    return 0;
}

