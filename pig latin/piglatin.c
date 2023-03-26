// Include necessary headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Required for the 'free' function
#include "pig.h" // Include the header file for the 'pig' function

int main() {
    char line[256]; // Declare a character array to hold user input

    // Start an infinite loop until the user enters an empty line
    while (1) {
        printf("Enter a line of English text (empty line to quit): "); // Prompt the user for input
        fgets(line, sizeof(line), stdin); // Read user input and store it in 'line' variable
        line[strcspn(line, "\n")] = '\0'; // Remove trailing newline character from the input string

        // Check if the input string is empty and break out of the loop if it is
        if (strlen(line) == 0) {
            break;
        }

        char *word = strtok(line, " "); // Tokenize the input string by splitting it into words using space as a delimiter

        // Loop through each word in the input string and convert it to pig latin
        while (word != NULL) {
            char *translation = pig(word); // Call the 'pig' function to translate the current word to pig latin
            printf("%s ", translation); // Print the translated word to the console
            free(translation); // Free the memory allocated to the 'translation' variable
            word = strtok(NULL, " "); // Move to the next word in the input string
        }

        printf("\n"); // Print a newline character after translating all the words in the input string
    }

    return 0; // Exit the program with status code 0
}