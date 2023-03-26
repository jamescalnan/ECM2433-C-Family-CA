#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "riffle.h"

int main() {
    srand(time(NULL));
    
    int N = 50;
    int trials = 30;

    printf("Riffle Average Quality\n");
    printf("------ ---------------\n");

    for (int i = 1; i <= 15; i++) {
        float avg_quality = average_quality(N, i);
        printf("%-6d %.13f\n", i, avg_quality);
    }

    return 0;
}
