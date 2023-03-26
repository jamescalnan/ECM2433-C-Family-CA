// Include necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define a function to determine the size of an array of different types
int size_of_array(void *L, int size) {
    int count = 0;
    
    // Check if the array is of char type
    if (size == sizeof(char)) {
        char *char_ptr = L;
        // Iterate through the array until a null character is found
        while (*char_ptr != '\0') {
            count++;
            char_ptr++;
        }
    // Check if the array is of int type
    } else if (size == sizeof(int)) {
        int *int_ptr = L;
        // Iterate through the array until a zero is found
        while (*int_ptr != 0) {
            count++;
            int_ptr++;
        }
    // Check if the array is of char* type (array of strings)
    } else if (size == sizeof(char*)) {
        char **char_ptr_ptr = L;
        // Iterate through the array until a NULL pointer is found
        while (*char_ptr_ptr != NULL) {
            count++;
            char_ptr_ptr++;
        }
    // If the array is of an unsupported type, print an error message and return -1
    } else {
        printf("Error: unsupported size.\n");
        return -1;
    }
    
    return count - 1;
}

// Define a function to perform a single riffle shuffle
void riffle_once(void *L, int size, void *work) {
    // Calculate the number of elements in the array (L)
    int count = size_of_array(L, size);

    // Split the array (L) into two halves
    int half = count / 2;

    // Initialize indices for the left and right halves of the array
    int l_index = 0;
    int r_index = half;

    // Cast the input array and work array as char pointers for easy manipulation
    char *l_ptr = (char *)L;
    char *w_ptr = (char *)work;

    int i;

    // Iterate through the array, selecting elements from the left or right half randomly
    for (i = 0; i < count; i++) {
        // If there are elements left in the left half, and either the right half is empty or the random
        // decision is to pick from the left half, select the next element from the left half
        if (l_index < half && (r_index >= count || rand() % 2 == 0)) {
            // Copy the selected element from the left half to the work array
            memcpy(w_ptr, l_ptr + l_index * size, size);
            l_index++;
        } else {
            // If the left half is empty or the random decision is to pick from the right half,
            // select the next element from the right half
            memcpy(w_ptr, l_ptr + r_index * size, size);
            r_index++;
        }
        // Move the work array pointer forward by the size of one element
        w_ptr += size;
    }

    // After shuffling, copy the shuffled elements from the work array back into the original array (L)
    memcpy(L, work, count * size);
}

// Define a function to perform a riffle shuffle N times on a given array of any type
void riffle(void *L, int size, int N) {
    int count = size_of_array(L, size);
    void *work = malloc(count * size);

    int i;

    // Perform the riffle shuffle N times
    for (i = 0; i < N; i++) {
        riffle_once(L, size, work);
    }

    // Free the allocated memory for the work array
    free(work);
}

// Define a function to check if the riffle shuffle was performed correctly
int check_shuffle(void *L, int size) {
    int count = size_of_array(L, size);
    // Allocate memory for a copy of the original array
    void *original = malloc(count * size);
    // Copy the original array to the newly allocated memory
    memcpy(original, L, count * size);
        // Allocate memory for a working array to be used during the shuffle
    void *work = malloc(count * size);
    // Perform a riffle shuffle on the input array
    riffle_once(L, size, work);

    int i;

    // Iterate over the original array
    for (i = 0; i < count; i++) {
        int found = 0;
        int j;
        // Iterate over the shuffled array
        for (j = 0; j < count; j++) {
            // Check if the original element exists in the shuffled array
            if (size == sizeof(char *)) { // It's an array of strings
                if (strcmp(((char **)original)[i], ((char **)L)[j]) == 0) {
                    found = 1;
                    break;
                }
            } else { // It's an array of integers
                if (((int *)original)[i] == ((int *)L)[j]) {
                    found = 1;
                    break;
                }
            }
        }
        // If the original element is not found in the shuffled array, return 0
        if (!found) {
            free(original);
            free(work);
            return 0;
        }
    }

    // Free the allocated memory and return 1, indicating a correct shuffle
    free(original);
    free(work);
    return 1;
}

// Define a function to calculate the quality of the shuffle
float quality(int *numbers) {
    int n = size_of_array(numbers, sizeof(int));

    int i;

    int count = 0;
    // Iterate through the array and count the number of increasing pairs
    for (i = 0; i < n - 1; i++) {
        if (numbers[i] < numbers[i + 1]) {
            count++;
        }
    }
    // Calculate and return the quality as the ratio of increasing pairs to the total number of pairs
    return (float)count / (n - 1);
}

// Define a function to calculate the average quality of N riffle shuffles
float average_quality(int N, int trials) {
    int *numbers = (int*)malloc((N+1) * sizeof(int));
    
    int t = 30;

    int i;

    float total_quality = 0;
    // Perform the riffle shuffle t times and calculate the total quality
    for (i = 0; i < t; i++) {
        int j;

        for (j = 0; j < N+1; j++) {
            numbers[j] = j + 1;
        }

        riffle(numbers, sizeof(int), trials);

        total_quality += quality(numbers);
    }
    // Free the allocated memory for the numbers array
    free(numbers);
    // Calculate and return the average quality
    return total_quality / t;
}
