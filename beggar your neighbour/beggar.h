#ifndef BEGGAR_H
#define BEGGAR_H

typedef struct {
    int *cards;
    int front;
    int rear;
    int size;
} Queue;

typedef struct {
    int shortest;
    int longest;
    int average;
} Stats;

int beggar(int Nplayers, int *deck, int talkative);
Stats statistics(int Nplayers, int games);
int finished(Queue *players, int Nplayers);

#endif // BEGGAR_H
