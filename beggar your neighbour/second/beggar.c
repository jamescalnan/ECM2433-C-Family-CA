#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

typedef struct {
    int shortest;
    int longest;
    double average;
} Stats;

int finished(int players[][52], int Nplayers);
int beggar(int Nplayers, int deck[], int verbose);
Stats statistics(int Nplayers, int games);

int finished(int players[][52], int Nplayers) {
    for (int i = 0; i < Nplayers; i++) {
        if (players[i][0] == 0) {
            return 0;  // return 1 when there is a winner
        }
    }
    return 1;  // return 0 otherwise
}


void print_deck(int deck[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", deck[i]);
    }
    printf("\n");
}

int beggar(int Nplayers, int deck[], int verbose) {
    int players[Nplayers][52];
    int piles[Nplayers][52];

    // Initialize players and piles arrays
    for (int i = 0; i < Nplayers; i++) {
        for (int j = 0; j < 52; j++) {
            players[i][j] = 0;
            piles[i][j] = 0;
        }
    }

    for (int i = 0; i < 52; i++) {
        int player = i % Nplayers;
        players[player][i / Nplayers] = deck[i];
    }

    int turn = 0;
    int currentPlayer = 0;
    while (!finished(players, Nplayers)) {
        turn++;

        if (verbose) {
            printf("Turn %d:\n", turn);
        }

        int card = players[currentPlayer][0];
        if (card == 0) {
            currentPlayer = (currentPlayer + 1) % Nplayers;
            continue;
        }

        for (int j = 0; j < 51; j++) {
            players[currentPlayer][j] = players[currentPlayer][j + 1];
        }
        players[currentPlayer][51] = 0;

        int nextPlayer = (currentPlayer + 1) % Nplayers;
        int penalty = card - 1;

        while (penalty > 0) {
            card = players[nextPlayer][0];

            if (card == 0) {
                break;
            }

            for (int j = 0; j < 51; j++) {
                players[nextPlayer][j] = players[nextPlayer][j + 1];
            }
            players[nextPlayer][51] = 0;

            piles[currentPlayer][card - 1]++;

            printf("Player %d got card %d\n", nextPlayer, card);
            printf("Player %d pile: ", currentPlayer);
            for (int j = 0; j < 13; j++) {
                printf("%d ", piles[currentPlayer][j]);
            }
            printf("\n");

            penalty--;

            if (card >= 11) {
                currentPlayer = nextPlayer;
                break;
            }
        }

        currentPlayer = (currentPlayer + 1) % Nplayers;
    }

    return turn;
}



