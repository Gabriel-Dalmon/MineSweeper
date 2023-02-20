// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <stdio.h>


typedef struct Case {
    int content;
    int state;
    int indicator;

} Case;


int main()
{

    int board[5][5];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d", board[i][j]);
        }
        printf("\n");
    }

    printf("%d", board[2][2]);

    // std::cout << "Hello World!\n";

}


//void displayBoard( Board board) {

// }
