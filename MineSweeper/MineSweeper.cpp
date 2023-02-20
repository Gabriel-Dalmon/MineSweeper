// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <stdio.h>


typedef struct Case {
    int content;
    int state;
    int indicator;

} Case;

float getArrayLength(int *a);

int main()
{

    int a[5];
    float aLength = getArrayLength(a);
    float aLengthOut = sizeof(a) / sizeof(a[0]);
    printf("%f\n", aLength);
    printf("%f\n", aLengthOut);

    Case board[5][5];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j].content = 0;
            printf("%d", board[i][j].content);
        }
        printf("\n");
    }

}

float getArrayLength(int *a) {
    float length = sizeof(*a) / sizeof(a[0]);
    return length;
}