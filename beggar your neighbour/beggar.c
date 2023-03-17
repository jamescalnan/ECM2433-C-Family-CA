#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "beggar.h"
#include "shuffle.h"

Queue create_queue(int size) {
    Queue queue;
    queue.cards = malloc(size * sizeof(int));
    queue.front = 0;
    queue.rear = 0;
    queue.size = size;
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

int beggar(int Nplayers, int *deck, int talkative) {
    int deck_size = 52;
    Queue players[Nplayers];
    for (int i = 0; i < Nplayers; i++) {
        players[i] = create_queue(deck_size);
    }
    
    for (int i = 0; i < deck_size; i++) {
        enqueue(&players[i % Nplayers], deck[i]);
    }
    
    Queue pile = create_queue(deck_size);
    Queue reward = create_queue(deck_size);
    int current_player = 0;
    int turns = 0;
    int penalty = 0;

    while (!finished(players, Nplayers)) {
        turns++;

        if (talkative) {
            printf("Turn %d: ", turns);
        }

        if (penalty == 0) {
            int card = dequeue(&players[current_player]);
            enqueue(&pile, card);

            if (card >= 11) {
                penalty = 15 - card;
            }

            if (talkative) {
                printf("Player %d plays %d\n", current_player, card);
            }
        } else {
            int card = dequeue(&players[current_player]);
            enqueue(&reward, card);

            if (card >= 11) {
                penalty = 15 - card;
            } else {
                penalty--;
            }

            if (talkative) {
                printf("Player %d pays %d\n", current_player, card);
            }

            if (penalty == 0) {
                while (!is_empty(&reward)) {
                    int won_card = dequeue(&reward);
                    enqueue(&players[current_player], won_card);
                }

                while (!is_empty(&pile)) {
                    int won_card = dequeue(&pile);
                    enqueue(&players[current_player], won_card);
                }
            }
        }

        current_player = (current_player + 1) % Nplayers;
    }

    for (int i = 0; i < Nplayers; i++) {
        free(players[i].cards);
    }
    
    free(pile.cards);
    free(reward.cards);
    
    return turns;
}

int finished(Queue *players, int Nplayers) {
    int empty_count = 0;
    for (int i = 0; i < Nplayers; i++) {
        if (is_empty(&players[i])) {
            empty_count++;
        }
    }
    return empty_count == Nplayers - 1;
}


Stats statistics(int Nplayers, int games) {
    Stats stats;
    stats.shortest = 100000;
    stats.longest = 0;
    stats.average = 0;

    int total_turns = 0;

    for (int i = 0; i < games; i++) {
        int deck[52];
        for (int j = 0; j < 52; j++) {
            deck[j] = j % 13 + 2;
        }

        shuffle(deck, 52, -1);

        int turns = beggar(Nplayers, deck, 0);
        total_turns += turns;

        if (turns < stats.shortest) {
            stats.shortest = turns;
        }

        if (turns > stats.longest) {
            stats.longest = turns;
        }
    }

    stats.average = total_turns / games;

    return stats;
}
