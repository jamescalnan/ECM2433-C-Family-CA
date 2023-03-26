// Include necessary header files
#include <stdbool.h> // For boolean data type
#include <string.h> // For string manipulation functions
#include <ctype.h> // For character manipulation functions
#include <stdlib.h> // For memory allocation functions
#include "pig.h" // Header file for pig function

// Function to check if a character is a vowel
bool is_vowel(char c) {
    c = tolower(c); // Convert the character to lowercase
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; // Check if the character is a vowel
}

// Function to check if a character is 'y' and is not the first character of a word
// and if the previous character is not a vowel
bool is_consonant_y(char c, const char *word, size_t index) {
    c = tolower(c); // Convert the character to lowercase
    return c == 'y' && index > 0 && !is_vowel(word[index - 1]); // Check if the character is 'y' and meets the conditions
}

// Function to convert a word to pig latin
char *pig(const char *word) {
    size_t len = strlen(word); // Get the length of the input word
    char *result = malloc(len + 4); // Allocate memory for the output string with extra space for "way", "ay", and null terminator

    // Check if the word starts with a vowel or if the first letter is 'y' and is not followed by a vowel
    if (is_vowel(word[0]) || (word[0] == 'y' && !is_vowel(word[1]))) {
        strcpy(result, word); // Copy the input word to the output string
        strcat(result, "way"); // Append "way" to the output string
    } else {
        size_t index = 0;
        // Loop through the word until a vowel or 'y' is found
        while (!is_vowel(word[index]) && !is_consonant_y(word[index], word, index)) {
            index++;
        }
        strcpy(result, word + index); // Copy the substring from the first vowel or 'y' to the end of the word to the output string
        strncat(result, word, index); // Append the substring from the beginning of the word to the first vowel or 'y' to the output string
        strcat(result, "ay"); // Append "ay" to the output string
    }

    return result; // Return the output string
}
