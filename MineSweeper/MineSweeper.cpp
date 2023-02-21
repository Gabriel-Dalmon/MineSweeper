// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <stdio.h>


typedef struct Case {
    int content;
    int isVisible; // 1 = visible, 0 = hidden;
    int indicator;

} Case;

typedef struct Board {
    int iSize;
    Case ** grid;

} Board;

void displayBoard(Board oBoard);

int main()
{

    Board oBoard;
    oBoard.iSize = 5;
    oBoard.grid[oBoard.iSize][oBoard.iSize];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            oBoard.grid[i][j].content = 0;
            oBoard.grid[i][j].isVisible = 0;
        }
    }
}

void displayBoard(Board oBoard) {
    for (int i = 0; i < oBoard.iSize; i++) {
        for (int j = 0; j < oBoard.iSize; j++) {
            if (oBoard.grid[i][j].isVisible == 0) {
                printf("[]");
            }
            else {
                printf("%d", oBoard.grid[i][j].content);
            }
        }
        printf("\n");
    }
}