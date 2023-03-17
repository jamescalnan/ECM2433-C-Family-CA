#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "riffle.h"

void print_int_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_str_array(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int numbers_size = sizeof(numbers) / sizeof(numbers[0]);

    printf("Original integers array:\n");
    print_int_array(numbers, numbers_size);

    riffle(numbers, numbers_size, sizeof(int), 5);

    printf("Shuffled integers array:\n");
    print_int_array(numbers, numbers_size);

    printf("Shuffle check: %d\n", check_shuffle(numbers, numbers_size));

    char *greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta",
                     "eta", "theta", "iota", "kappa", "lambda", "mu"};
    int greek_size = sizeof(greek) / sizeof(greek[0]);

    printf("Original Greek letters array:\n");
    print_str_array(greek, greek_size);

    riffle(greek, greek_size, sizeof(char *), 5);

    printf("Shuffled Greek letters array:\n");
    print_str_array(greek, greek_size);

    printf("Shuffle check: %d\n", check_shuffle(greek, greek_size));

    return 0;
}
