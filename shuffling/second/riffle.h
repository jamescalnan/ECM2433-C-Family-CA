#ifndef RIFFLE_H
#define RIFFLE_H

void riffle_once(void *L, int size, int elem_size, void *work);
void riffle(void *L, int size, int elem_size, int N);
int check_shuffle(void *L, int size, int elem_size);
float quality(int *numbers, int size);
float average_quality(int N, int trials, int size);

#endif // RIFFLE_H
