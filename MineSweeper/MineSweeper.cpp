// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <stdio.h>


typedef struct Case {
    int content;
    int state;
    int indicator;

} Case;


//void displayBoard(Case board[][]);

int main()
{

    Case board[5][5];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j].content = 0;
        }
        printf("\n");
    }

    for (int i = 0; i < 5; i++) {
        printf("%d", i);
    }

    for (int i = 0; i < 5; i++)
        printf("%d", i);
        for (int j = 0; j < 5; j++) {
            printf("%d", board[i][j].content);
        }
        printf("\n");
    }


}


//void displayBoard( Case board[][]) {
    
//}


