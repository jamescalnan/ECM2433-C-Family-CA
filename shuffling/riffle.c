#include <stdlib.h>
#include <string.h>
#include <time.h>

void riffle_once(void *L, int size, void *work) {
    int len = size * (sizeof L / sizeof ((char*)L)[0]);
    char *left = L;
    char *right = (char*)L + len / 2;
    char *p = work;
    while (left < (char*)L + len / 2 && right < (char*)L + len) {
        if (rand() % 2 == 0) {
            memcpy(p, left, size);
            left += size;
        } else {
            memcpy(p, right, size);
            right += size;
        }
        p += size;
    }
    if (left < (char*)L + len / 2) {
        memcpy(p, left, (char*)L + len / 2 - left);
    } else {
        memcpy(p, right, (char*)L + len - right);
    }
    memcpy(L, work, len);
}

void riffle(void *L, int size, int N) {
    void *work = malloc(size * (sizeof L / sizeof ((char*)L)[0]));
    for (int i = 0; i < N; i++) {
        riffle_once(L, size, work);
    }
    free(work);
}

int check_shuffle(void *L, int size) {
    int len = size * (sizeof L / sizeof ((char*)L)[0]);
    void *work = malloc(len);
    memcpy(work, L, len);
    riffle_once(L, size, work);
    riffle_once(L, size, work);
    riffle_once(L, size, work);
    for (char *p = L; p < (char*)L + len; p += size) {
        int found = 0;
        for (char *q = work; q < (char*)work + len; q += size) {
            if (memcmp(p, q, size) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            free(work);
            return 0;
        }
    }
    free(work);
    return 1;
}

float quality(int *numbers, int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        if (numbers[i] < numbers[i + 1]) {
            count++;
        }
    }
    return (float)count / (n - 1);
}

float average_quality(int N, int trials) {
    int *numbers = malloc(N * sizeof(int));
    float total_quality = 0;
    for (int i = 0; i < trials; i++) {
        for (int j = 0; j < N; j++) {
            numbers[j] = j;
        }
        riffle(numbers, sizeof(int), 7);
        total_quality += quality(numbers, N);
    }
    free(numbers);
    return total_quality / trials;
}
