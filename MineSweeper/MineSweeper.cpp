// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <time.h>

typedef struct Case {
    int content;
    int isVisible; // 1 = visible, 0 = hidden;
    int indicator;

} Case;

typedef struct Board {
    Case grid[5][5];
    int size;
} Board;


Board init(int size);
void displayBoard(Board oBoard);

int main()
{

    Board table = init(5);
    displayBoard(table);
    int r = time(NULL) % 2;
    printf("%d", r);


}

void displayBoard(Board oBoard) {
    for (int i = 0; i < oBoard.size; i++) {
        for (int j = 0; j < oBoard.size; j++) {
            if (oBoard.grid[i][j].isVisible == 0) {
                printf("[]");
            }
            else {
                printf("%d", oBoard.grid[i][j].content);
            }
        }
        printf("\n");
    };

}

Board init(int size) {
    Board table;
    table.size = size;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            table.grid[i][j].content = 0;
            table.grid[i][j].isVisible = 0;
        }
    };
    
    return table;
}