#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "riffle.h"

#define NUM_INTS 20
#define NUM_GREEK 12

char *greek[] = { "alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta",
                  "iota", "kappa", "lambda", "mu" };

void print_int_array(int *arr, int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void print_greek_array(char **arr, int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%s ", arr[i]);
    }
    printf("]\n");
}

int check_shuffle_int(int *arr, int *shuffled_arr, int size) {
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < size; j++) {
            if (arr[i] == shuffled_arr[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < size; j++) {
            if (shuffled_arr[i] == arr[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }
    return 1;
}

int check_shuffle_greek(char **arr, char **shuffled_arr, int size) {
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < size; j++) {
            if (strcmp(arr[i], shuffled_arr[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < size; j++) {
            if (strcmp(shuffled_arr[i], arr[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int ints[NUM_INTS];
    char *greek_shuffled[NUM_GREEK];
    srand(time(NULL));

    // Initialize arrays
    for (int i = 0; i < NUM_INTS; i++) {
        ints[i] = i + 1;
    }

    // Shuffle ints
    riffle(ints, sizeof(int), NUM_INTS);
    printf("Shuffled ints: ");
    print_int_array(ints, NUM_INTS);

    // Shuffle ints
    riffle(ints, sizeof(int), NUM_INTS);
    printf("Shuffled ints: ");
    print_int_array(ints, NUM_INTS);

    // Shuffle Greek
    memcpy(greek_shuffled, greek, sizeof(greek));
    riffle(greek_shuffled, sizeof(char*), NUM_GREEK);
    printf("Shuffled Greek: ");
    print_greek_array(greek_shuffled, NUM_GREEK);

    // Check shuffled Greek
    if (check_shuffle_greek(greek, greek_shuffled, NUM_GREEK)) {
        printf("Greek shuffled correctly!\n");
    } else {
        printf("Error: Greek not shuffled correctly.\n");
    }

    return 0;
}
