#ifndef RIFFLE_H
#define RIFFLE_H

void riffle_once(void *L, int size, void *work);
void riffle(void *L, int size, int N);
int check_shuffle(void *L, int size);
float quality(int *numbers, int n);
float average_quality(int N, int trials);

#endif
