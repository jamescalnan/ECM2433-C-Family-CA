#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "riffle.h"

int main() {
    srand(time(NULL));

    int array_size = 50;
    int max_N = 15;
    int trials = 30;

    printf("Average quality for riffle shuffle:\n");
    printf(" N | Avg. Quality\n");
    printf("---------------\n");

    for (int N = 1; N <= max_N; N++) {
        float avg_quality = average_quality(N, trials, array_size);
        printf("%2d | %.4f\n", N, avg_quality);
    }

    return 0;
}
