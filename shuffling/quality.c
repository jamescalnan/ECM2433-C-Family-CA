#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "riffle.h"

#define TRIALS 30


int main() {
    srand(time(NULL));
    
    // Shuffle an array of integers from 0 to 20
    int arr1[20];
    for (int i = 0; i < 20; i++) {
        arr1[i] = i;
    }
    riffle(arr1, sizeof(int), 20);
    printf("Shuffled array of integers from 0 to 20:\n");
    for (int i = 0; i < 20; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");
    int check1 = check_shuffle(arr1, 20);;
    printf("Check shuffle for shuffled array of integers from 0 to 20: %d\n", check1);
    
    // Shuffle an array of Greek letter names
    char *greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu"};
    int size = sizeof(greek)/sizeof(greek[0]);
    riffle(greek, sizeof(char*), size);
    printf("\nShuffled array of Greek letter names:\n");
    for (int i = 0; i < size; i++) {
        printf("%s ", greek[i]);
    }
    printf("\n");
    int check2 = check_shuffle(greek, size);
    printf("Check shuffle for shuffled array of Greek letter names: %d\n", check2);
    
    // Evaluate average quality for array of length 50 with different numbers of riffles
    printf("\nAverage quality of shuffled array of integers from 0 to 49 with different numbers of riffles:\n");
    for (int n = 1; n <= 15; n++) {
        float avg_quality = average_quality(50, TRIALS * n);
        printf("Number of riffles: %d, Average quality: %f\n", n, avg_quality);
    }
    
    return 0;
}