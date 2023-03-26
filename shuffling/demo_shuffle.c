// Include necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "riffle.h"

// Define an array of Greek letters
char *greek[] = {
    "alpha", "beta", "gamma", "delta", "epsilon", "zeta",
    "eta", "theta", "iota", "kappa", "lambda", "mu"
};

// Define a function to print an array of integers
void print_int_array(int *arr, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Define the main function
int main() {
    srand(time(NULL)); // Seed the random number generator with the current time

    int count = sizeof(greek) / sizeof(greek[0]); // Calculate the number of elements in the greek array

    int N = 10; // Define the number of riffle shuffles to perform

    int i;

    printf("Original list:\n"); // Print the original list of Greek letters
    for (i = 0; i < count; i++) {
        printf("%d\t%s\n", i, greek[i]);
    }

    riffle(greek, sizeof(char *), N); // Shuffle the array of Greek letters

    printf("\nShuffled list after %d riffle shuffles:\n", N); // Print the shuffled list of Greek letters
    for (i = 0; i < count; i++) {
        printf("%d\t%s\n", i, greek[i]);
    }

    int check_result = check_shuffle(greek, sizeof(char *)); // Check whether the shuffle is valid

    printf("\nShuffle check result: %d\n", check_result); // Print the result of the shuffle check

    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}; // Define an array of integers
    int num_count = sizeof(numbers) / sizeof(numbers[0]); // Calculate the number of elements in the numbers array

    printf("\nOriginal integer list:\n"); // Print the original list of integers
    print_int_array(numbers, num_count);

    // N = 10;

    riffle(numbers, sizeof(int), N); // Shuffle the array of integers

    printf("\nShuffled integer list after %d riffle shuffles:\n", N); // Print the shuffled list of integers
    print_int_array(numbers, num_count);

    check_result = check_shuffle(numbers, sizeof(int)); // Check whether the shuffle is valid

    printf("\nShuffle check result: %d\n", check_result); // Print the result of the shuffle check

    return 0; // Return 0 to indicate successful program execution
}
