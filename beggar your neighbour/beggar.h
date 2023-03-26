#ifndef BEGGAR_H
#define BEGGAR_H

typedef struct {
    int *cards;
    int front;
    int rear;
    int size;
    int total_players;
} Queue;

typedef struct {
    int shortest;
    int longest;
    float average;
} Stats;

int beggar(int Nplayers, int *deck, int talkative);
Stats statistics(int Nplayers, int games);
int finished(Queue *players);

#endif // BEGGAR_H
