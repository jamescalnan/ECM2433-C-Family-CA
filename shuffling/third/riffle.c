#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "riffle.h"

void riffle_once(void *L, int size, int elem_size, void *work) {
    char *src = (char *)L;
    char *dst = (char *)work;
    int n = size / 2;

    for (int i = 0; i < n; i++) {
        memcpy(dst + i * 2 * elem_size, src + i * elem_size, elem_size);
        memcpy(dst + (i * 2 + 1) * elem_size, src + (n + i) * elem_size, elem_size);
    }

    memcpy(L, work, size * elem_size);
}

void riffle(void *L, int size, int elem_size, int N) {
    char *work = (char *)malloc(size * elem_size);

    for (int i = 0; i < N; i++) {
        riffle_once(L, size, elem_size, work);
    }

    free(work);
}

int check_shuffle(void *L, int size, int elem_size) {
    int count = 0;
    char *src = (char *)L;

    for (int i = 0; i < size - 1; i++) {
        if (memcmp(src + i * elem_size, src + (i + 1) * elem_size, elem_size) < 0) {
            count++;
        }
    }

    return count == size - 1;
}

float quality(int *numbers, int size) {
    int count = 0;
    for (int i = 0; i < size - 1; i++) {
        if (numbers[i + 1] > numbers[i]) {
            count++;
        }
    }
    return (float)count / (size - 1);
}

float average_quality(int N, int trials, int size) {
    float total_quality = 0;
    int *numbers = (int *)malloc(size * sizeof(int));

    for (int t = 0; t < trials; t++) {
        for (int i = 0; i < size; i++) {
            numbers[i] = i;
        }

        riffle(numbers, size, sizeof(int), N);
        total_quality += quality(numbers, size);
    }

    free(numbers);
    return total_quality / trials;
}
