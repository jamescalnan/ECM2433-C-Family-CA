#include <stdio.h>
#include <stdlib.h>
#include "beggar.h"
#include "shuffle.h"

int main(int argc, char *argv[]) {
    // Check that the correct number of command line arguments were provided
    if (argc != 3) {
        // Print an error message indicating the correct usage of the program
        fprintf(stderr, "Usage: %s <max number of players> <number of trials>\n", argv[0]);
        return 1; // Return a non-zero exit status to indicate an error
    }

    // Convert the command line arguments to integers
    int max_players = atoi(argv[1]);
    int trials = atoi(argv[2]);

    int Nplayers;

    // Print a header for the output columns
    printf("%-16s  %-10s %-10s %-10s\n", "Number of Players", "Shortest", "Longest", "Average");

    // Loop over the number of players from 2 up to the maximum
    for (Nplayers = 2; Nplayers <= max_players; Nplayers++) {
        // Run the game for the current number of players and specified number of trials
        Stats stats = statistics(Nplayers, trials);

        // Print the results for the current number of players with fixed-width columns
        printf("%-16d   %-10d %-10d %-10.0f\n", Nplayers, stats.shortest, stats.longest, stats.average);
    }

    return 0; // Return a zero exit status to indicate success
}
