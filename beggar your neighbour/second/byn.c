#include <stdio.h>
#include <stdlib.h>
#include "shuffle.h"

typedef struct {
    int shortest;
    int longest;
    double average;
} Stats;

int finished(int *players, int Nplayers);
void play_turn(int *players, int Nplayers, int *piles);
Stats statistics(int Nplayers, int games);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s max_players trials\n", argv[0]);
        return 1;
    }

    int max_players = atoi(argv[1]);
    int trials = atoi(argv[2]);

    for (int i = 2; i <= max_players; i++) {
        Stats stats = statistics(i, trials);
        printf("Number of players: %d\n", i);
        printf("Shortest game: %d turns\n", stats.shortest);
        printf("Longest game: %d turns\n", stats.longest);
        printf("Average game length: %.2f turns\n\n", stats.average);
    }

    return 0;
}

int finished(int *players, int Nplayers) {
    int finished_players = 0;
    for (int i = 0; i < Nplayers; i++) {
        if (players[i] == 0) {
            finished_players++;
        }
    }
    return finished_players == Nplayers - 1;
}

void play_turn(int *players, int Nplayers, int *piles) {
    int currentPlayer = 0;
    while (players[currentPlayer] == 0) {
        currentPlayer++;
    }

    int nextPlayer = (currentPlayer + 1) % Nplayers;
    while (players[nextPlayer] == 0) {
        nextPlayer = (nextPlayer + 1) % Nplayers;
    }

    piles[currentPlayer] += piles[nextPlayer] + 1;
    piles[nextPlayer] = 0;

    players[currentPlayer]--;
    players[nextPlayer]++;

    shuffle(players, Nplayers, Nplayers);
}

Stats statistics(int Nplayers, int games) {
    int total_turns = 0;
    int shortest_game = -1;
    int longest_game = 0;

    for (int i = 0; i < games; i++) {
        int players[Nplayers];
        for (int j = 0; j < Nplayers; j++) {
            players[j] = 52 / Nplayers;
        }

        int piles[Nplayers];
        for (int j = 0; j < Nplayers; j++) {
            piles[j] = 0;
        }

        shuffle(players, Nplayers, Nplayers);

        int turns = 0;
        while (!finished(players, Nplayers)) {
            play_turn(players, Nplayers, piles);
            turns++;
        }

        total_turns += turns;
        if (shortest_game == -1 || turns < shortest_game) {
            shortest_game = turns;
        }
        if (turns > longest_game) {
            longest_game = turns;
        }
    }

    Stats result;
    result.shortest = shortest_game;
    result.longest = longest_game;
    result.average = (double) total_turns / games;
    return result;
}
