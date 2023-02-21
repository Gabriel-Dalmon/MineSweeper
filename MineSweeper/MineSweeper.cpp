// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <stdio.h>


typedef struct Case {
    int content;
    int state;
    int indicator;

} Case;

typedef struct Board {
    Case** grid;
    int size;
} Board;


Board init(int size);
//void displayBoard(Case board[][]);

int main()
{

    Board table = init(5);
    

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d", table.grid[i][j].content);
        }
        printf("\n");
    };

}

Board init(int size) {
    Board table;
    table.size = size;
    table.grid[size][size];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            table.grid[i][j].content = 0;
        }
    };
    
    return table;
}