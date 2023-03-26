// include necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "riffle.h" // assumes that "riffle.h" header file is present in the same directory

// main function
int main() {

    // seed the random number generator with the current time
    srand(time(NULL));
    
    // set the number of riffle shuffles to perform
    int N = 50;

    // print a header for the output
    printf("Riffle Average Quality +- 0.5\n");
    printf("------ --------------- ------\n");

    int i;

    // loop through a range of interleaving sizes and calculate and output the average quality and difference from 0.5 for each size
    for (i = 1; i <= 15; i++) {
        float avg_quality = average_quality(N, i);
        float diff = 0.5 - avg_quality;
        printf("%-6d %13.13f %6.3f\n", i, avg_quality, diff);
    }

    // indicate successful completion of the program
    return 0;
}
