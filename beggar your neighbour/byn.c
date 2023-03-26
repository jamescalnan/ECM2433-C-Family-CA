#include <stdio.h>
#include <stdlib.h>
#include "beggar.h"
#include "shuffle.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <max number of players> <number of trials>\n", argv[0]);
        return 1;
    }

    int max_players = atoi(argv[1]);
    int trials = atoi(argv[2]);

    for (int Nplayers = 2; Nplayers <= max_players; Nplayers++) {
        Stats stats = statistics(Nplayers, trials);
        printf("For %d players: shortest = %d, longest = %d, average = %.0f\n", Nplayers, stats.shortest, stats.longest, stats.average);
    }

    return 0;
}
