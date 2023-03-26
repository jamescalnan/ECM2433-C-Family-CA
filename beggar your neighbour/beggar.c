#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "beggar.h"
#include "shuffle.h"

Queue create_queue(int size, int total_players) {
    Queue queue;
    queue.cards = malloc(size * sizeof(int));
    queue.front = 0;
    queue.rear = 0;
    queue.size = size;
    queue.total_players = total_players;

    for (int i = 0; i < size; i++) {
        queue.cards[i] = -1;
    }

    return queue;
}

bool is_empty(Queue *queue) {
    return queue->front == queue->rear;
}

void enqueue(Queue *queue, int card) {
    queue->cards[queue->rear] = card;
    queue->rear = (queue->rear + 1) % queue->size;
}

int dequeue(Queue *queue) {
    int card = queue->cards[queue->front];
    queue->front = (queue->front + 1) % queue->size;
    return card;
}


Queue take_turn(Queue *player, Queue *pile, int *penalty) {
    Queue reward = create_queue(pile->size, player->total_players);

    if (*penalty == 0) {
        int card = dequeue(player);
        enqueue(pile, card);

        if (card >= 11) {
            *penalty = 15 - card;
        }
    } else {
        int card = dequeue(player);
        enqueue(&reward, card);

        if (card >= 11) {
            *penalty = 15 - card;
        } else {
            (*penalty)--;
        }

        if (*penalty == 0) {
            while (!is_empty(&reward)) {
                int won_card = dequeue(&reward);
                enqueue(player, won_card);
            }

            while (!is_empty(pile)) {
                int won_card = dequeue(pile);
                enqueue(player, won_card);
            }
        }
    }

    return reward;
}

int beggar(int Nplayers, int *deck, int talkative) {
    int deck_size = 52;
    Queue players[Nplayers];
    for (int i = 0; i < Nplayers; i++) {
        players[i] = create_queue(deck_size, Nplayers);
    }
    
    for (int i = 0; i < deck_size; i++) {
        enqueue(&players[i % Nplayers], deck[i]);
    }

    Queue pile = create_queue(deck_size, Nplayers);
    int current_player = 0;
    int turns = 0;
    int penalty = 0;

    while (!finished(players)) { 
        turns++;

        if (talkative) {
            printf("Turn %d ", turns);

            if (penalty == 0) {
                printf("Top card in pile is %d, so player %d should lay a single card\n", pile.cards[pile.front], current_player);
            } else {
                printf("Top card is %d, so player %d should lay %d penalty cards\n", pile.cards[pile.front], current_player, penalty);
            }
        }

        Queue reward = take_turn(&players[current_player], &pile, &penalty);

        if (talkative) {
            printf("Pile: ");
            for (int i = pile.front; i != pile.rear; i = (i + 1) % pile.size) {
                printf("%d, ", pile.cards[i]);
            }
            printf("\n");

            for (int i = 0; i < Nplayers; i++) {
                if (i == current_player) {
                    printf("* %d: ", i);
                } else {
                    printf("  %d: ", i);
                }

                for (int j = players[i].front; j != players[i].rear; j = (j + 1) % players[i].size) {
                    printf("%d, ", players[i].cards[j]);
                }
                printf("\n");
            }
        }

        current_player = (current_player + 1) % Nplayers;
        free(reward.cards);
    }

    for (int i = 0; i < Nplayers; i++) {
        free(players[i].cards);
    }
    
    free(pile.cards);
    
    return turns;
}



int finished(Queue *players) {
    int empty_count = 0;
    int Nplayers = players[0].total_players;
    for (int i = 0; i < Nplayers; i++) {
        if (!is_empty(&players[i]) && players[i].cards[players[i].front] != -1) {
            empty_count++;
        }
    }
    return empty_count == Nplayers - 1;
}


Stats statistics(int Nplayers, int games) {
    Stats stats;
    stats.shortest = 100000;
    stats.longest = 0;
    stats.average = 0.0f;

    float total_turns = 0.0f;

    for (int i = 0; i < games; i++) {
        int deck[52];
        for (int j = 0; j < 52; j++) {
            deck[j] = j % 13 + 2;
        }

        shuffle(deck, 52, -1);

        int turns = beggar(Nplayers, deck, 0);
        total_turns += (float)turns;

        if (turns < stats.shortest) {
            stats.shortest = turns;
        }

        if (turns > stats.longest) {
            stats.longest = turns;
        }

    }

    if (stats.shortest == 100000) {
        stats.average = -1.0f;
    } else {
        stats.average = total_turns / (float) games;
    }

    return stats;
}

