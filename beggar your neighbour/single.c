#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "beggar.h"
#include "shuffle.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of players>\n", argv[0]);
        return 1;
    }

    int Nplayers = atoi(argv[1]);
    int deck[52];

    // Initialize and shuffle the deck
    for (int i = 0; i < 52; i++) {
        deck[i] = i % 13 + 2;
    }
    shuffle(deck, 52, time(NULL));

    int turns = beggar(Nplayers, deck, 1);
    printf("Game finished in %d turns.\n", turns);

    return 0;
}
