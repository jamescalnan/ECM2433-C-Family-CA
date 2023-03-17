#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "riffle.h"

char *greek[] = {
    "alpha", "beta", "gamma", "delta", "epsilon", "zeta",
    "eta", "theta", "iota", "kappa", "lambda", "mu"
};

int main() {
    int count = sizeof(greek) / sizeof(greek[0]);

    int N = 1 + rand() % 7;

    printf("Original list:\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\n", i, greek[i]);
    }

    riffle(greek, sizeof(char *), count, N);

    printf("\nShuffled list after %d riffle shuffles:\n", N);
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\n", i, greek[i]);
    }

    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int num_count = sizeof(numbers) / sizeof(numbers[0]);
    int check_result = check_shuffle(numbers, sizeof(int), num_count);
    printf("\nShuffle check result: %d\n", check_result);

    return 0;
}