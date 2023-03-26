#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "beggar.h"
#include "shuffle.h"

int main(int argc, char *argv[]) {
    // Check that the correct number of command line arguments were provided
    if (argc != 2) {
        // Print an error message indicating the correct usage of the program
        fprintf(stderr, "Usage: %s <number of players>\n", argv[0]);
        return 1; // Return a non-zero exit status to indicate an error
    }

    // Convert the command line argument to an integer
    int Nplayers = atoi(argv[1]);

    int deck[52];

    int i;

    // Initialize and shuffle the deck
    for (i = 0; i < 52; i++) {
        deck[i] = i % 13 + 2;
    }
    shuffle(deck, 52, time(NULL));

    // Play the game with the specified number of players and shuffled deck, starting with player 1
    int turns = beggar(Nplayers, deck, 1);

    // Print the number of turns taken to complete the game
    printf("Game finished in %d turns.\n", turns);

    return 0; // Return a zero exit status to indicate success
}
