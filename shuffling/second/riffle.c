#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void riffle_once(void *L, int size, int count, void *work) {
    // srand(time(NULL)); 
    int half = count / 2;
    int l_index = 0;
    int r_index = half;
    char *l_ptr = (char *)L;
    char *w_ptr = (char *)work;

    for (int i = 0; i < count; i++) {
        if (l_index < half && (r_index >= count || rand() % 2 == 0)) {
            memcpy(w_ptr, l_ptr + l_index * size, size);
            l_index++;
        } else {
            memcpy(w_ptr, l_ptr + r_index * size, size);
            r_index++;
        }
        w_ptr += size;
    }

    memcpy(L, work, count * size);
}

void riffle(void *L, int size, int count, int N) {
    void *work = malloc(count * size);

    for (int i = 0; i < N; i++) {
        riffle_once(L, size, count, work);
    }

    free(work);
}

int check_shuffle(void *L, int size, int count) {
    int *original = malloc(count * size);
    memcpy(original, L, count * size);

    void *work = malloc(count * size);
    riffle_once(L, size, count, work);

    int *shuffled = (int *)L;

    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < count; j++) {
            if (original[i] == shuffled[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            free(original);
            free(work);
            return 0;
        }
    }

    free(original);
    free(work);
    return 1;
}

float quality(int *numbers, int count) {
    int greater_count = 0;

    for (int i = 1; i < count; i++) {
        if (numbers[i] > numbers[i - 1]) {
            greater_count++;
        }
    }

    return (float)greater_count / (count - 1);
}

float average_quality(int N, int trials) {
    srand(time(NULL));

    float total_quality = 0.0f;

    for (int t = 0; t < trials; t++) {
        int *numbers = malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            numbers[i] = i;
        }

        riffle(numbers, sizeof(int), N, t + 1);
        float q = quality(numbers, N);
        total_quality += q;

        free(numbers);
    }

    return total_quality / trials;
}
