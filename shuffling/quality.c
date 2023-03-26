#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "riffle.h"

int main() {
    srand(time(NULL));
    
    int N = 50;

    printf("Riffle Average Quality +- 0.5\n");
    printf("------ --------------- ------\n");

    int i;

    for (i = 1; i <= 15; i++) {
        float avg_quality = average_quality(N, i);
        float diff = 0.5 - avg_quality;
        printf("%-6d %13.13f %6.3f\n", i, avg_quality, diff);
    }

    return 0;
}
