#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "pig.h"

bool is_vowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

char *pig(const char *word) {
    size_t len = strlen(word);
    char *result = malloc(len + 4); // Extra space for "way", "ay", and null terminator

    if (is_vowel(word[0]) || (word[0] == 'y' && !is_vowel(word[1]))) {
        strcpy(result, word);
        strcat(result, "way");
    } else {
        size_t index = 0;
        while (!is_vowel(word[index]) && word[index] != 'y') {
            index++;
        }
        strcpy(result, word + index);
        strncat(result, word, index);
        strcat(result, "ay");
    }

    return result;
}
