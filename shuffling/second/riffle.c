#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int size_of_array(void *L, int size) {
    int count = 0;
    
    if (size == sizeof(char)) {
        char *char_ptr = L;
        while (*char_ptr != '\0') {
            count++;
            char_ptr++;
        }
    } else if (size == sizeof(int)) {
        int *int_ptr = L;
        while (*int_ptr != 0) {
            count++;
            int_ptr++;
        }
    } else if (size == sizeof(char*)) {
        char **char_ptr_ptr = L;
        while (*char_ptr_ptr != NULL) {
            count++;
            char_ptr_ptr++;
        }
    } else {
        printf("Error: unsupported size.\n");
        return -1;
    }
    
    return count - 1;
}


void riffle_once(void *L, int size, void *work) {
    int count = size_of_array(L, size);
    int half = count / 2;
    int l_index = 0;
    int r_index = half;
    char *l_ptr = (char *)L;
    char *w_ptr = (char *)work;

    // printf("Before riffle_once:\n");
    // for (int i = 0; i < count; i++) {
    //     if (i == half) {
    //         printf("| ");
    //     }
    //     if (size == sizeof(int)) {
    //         printf("%d ", ((int*)L)[i]);
    //     } else if (size == sizeof(char)) {
    //         printf("%c ", ((char*)L)[i]);
    //     }
    // }
    // printf("\n");

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

    // printf("After riffle_once:\n");
    // for (int i = 0; i < count; i++) {
    //     if (i == half) {
    //         printf("| ");
    //     }
    //     if (size == sizeof(int)) {
    //         printf("%d ", ((int*)work)[i]);
    //     } else if (size == sizeof(char)) {
    //         printf("%c ", ((char*)work)[i]);
    //     }
    // }
    // printf("\n");

    memcpy(L, work, count * size);
}

void riffle(void *L, int size, int N) {
    int count = size_of_array(L, size);
    void *work = malloc(count * size);

    for (int i = 0; i < N; i++) {
        riffle_once(L, size, work);
    }

    free(work);
}


/**
 * Check whether a single riffle shuffle has been correctly performed on an integer array.
 * 
 * @param L A pointer to the integer array to be checked.
 * @param size The size of each element in the array (in bytes).
 * @param count The number of elements in the array.
 * @return 1 if the shuffle has been correctly performed, 0 otherwise.
 */
int check_shuffle(void *L, int size, int count) {
    // Allocate memory for a copy of the original array
    int *original = malloc(count * size);
    // Copy the original array to the newly allocated memory
    memcpy(original, L, count * size);

    // Allocate memory for a working array to be used during the shuffle
    void *work = malloc(count * size);
    // Perform a riffle shuffle on the input array
    riffle_once(L, size, work);

    // Cast the shuffled array back to an integer array
    int *shuffled = (int *)L;

    // Iterate over the original array
    for (int i = 0; i < count; i++) {
        int found = 0;
        // Iterate over the shuffled array
        for (int j = 0; j < count; j++) {
            // Check if the original element exists in the shuffled array
            if (original[i] == shuffled[j]) {
                found = 1;
                break;
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


// float quality(int *numbers, int count) {
//     int greater_count = 0;

//     for (int i = 1; i < count; i++) {
//         if (numbers[i] > numbers[i - 1]) {
//             greater_count++;
//         }
//     }

//     return (float)greater_count / (count - 1);
// }

// float average_quality(int N, int trials) {
//     srand(time(NULL));

//     float total_quality = 0.0f;

//     for (int t = 0; t < trials; t++) {
//         int *numbers = malloc(N * sizeof(int));
//         for (int i = 0; i < N; i++) {
//             numbers[i] = i;
//         }

//         riffle(numbers, sizeof(int), t + 1);
//         float q = quality(numbers, N);
//         total_quality += q;

//         free(numbers);
//     }

//     return total_quality / trials;
// }

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
    int *numbers = (int*)malloc((N+1) * sizeof(int));

    

    float total_quality = 0;
    for (int i = 0; i < trials; i++) {
        for (int i = 0; i < N+1; i++) {
            numbers[i] = i + 1;
        }

        riffle(numbers, sizeof(int), 7);

        total_quality += quality(numbers, N);
    }
    free(numbers);
    return total_quality / trials;
}


