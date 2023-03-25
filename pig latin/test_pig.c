#include <stdio.h>
#include <stdlib.h>
#include "pig.h"

void test(const char *word, const char *expected) {
    char *result = pig(word);
    printf("%-10s => %-10s\n", word, result);
    free(result);
}

int main() {
    test("happy", "appyhay");
    test("duck", "uckday");
    test("glove", "oveglay");
    test("evil", "evilway");
    test("eight", "eightway");
    test("yowler", "owleryay");
    test("crystal", "ystalcray");

    return 0;
}
