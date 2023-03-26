#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Add this line
#include "pig.h"

int main() {
    char line[256];

    while (1) {
        printf("Enter a line of English text (empty line to quit): ");
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0'; // remove trailing newline

        if (strlen(line) == 0) {
            break;
        }

        char *word = strtok(line, " ");
        while (word != NULL) {
            char *translation = pig(word);
            printf("%s ", translation);
            free(translation);
            word = strtok(NULL, " ");
        }

        printf("\n");
    }

    return 0;
}
