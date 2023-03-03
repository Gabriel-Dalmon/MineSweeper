

#include <stdio.h>
#include <stdlib.h>
#include "msutils.h"


void getInput(int* dest) {
    int res = scanf_s("%d", dest);
    while (res != 1) {
        clearSTDIN();
        printf("The input has to be an integer: ");
        res = scanf_s("%d", dest);
    }
}

void clearSTDIN() {
    while (getchar() != '\n');
}

void oddToEvenByLower(int* number) {
    if (*number % 2 == 1) {
        (*number)--;
    }
}