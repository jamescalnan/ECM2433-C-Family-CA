// Include necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pig.h"  // Includes a user-defined function pig(char*) from a pig.h header file.

// Define a function to test the pig(char*) function. It takes two arguments: a word to test and the expected pig latin output.
void test(const char *word, const char *expected) {
    char *result = pig(word); //Call the pig(char*) function with the given word and store the result in a character pointer.
    
    // Compare the result obtained from pig(char*) with the expected output.
    if (strcmp(result, expected) == 0) {
        printf("Test passed: %-10s => %-10s\n", word, result); // Print the word and the pig latin output if the result matches the expected output.
    } else {
        printf("Test failed: %-10s => %-10s (expected %s)\n", word, result, expected); // Print the word, the actual pig latin output, and the expected output if the result does not match the expected output.
    }
    free(result); // Free the memory allocated for the result pointer.
}

// Main function to run the test cases.
int main() {
    // Call the test function for each test case with the word to test and the expected pig latin output.
    test("happy", "appyhay");
    test("duck", "uckday");
    test("glove", "oveglay");
    test("evil", "evilway");
    test("eight", "eightway");
    test("yowler", "owleryay");
    test("crystal", "ystalcray");

    return 0; // Return 0 to indicate successful program execution.
}
