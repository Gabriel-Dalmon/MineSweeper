// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Case {
    int content;
    int isVisible; // 1 = visible, 0 = hidden;
    int indicator;

} Case;

typedef struct Board {
    Case* grid;
    int size;
} Board;

Board init(int size, int mines);
void displayBoard(Board oBoard);
void reveal(Board* table, int x, int y);
void check(Board* table, int x, int y);

int main()
{
    int size;
    printf("Entrez une taille de grille : ");
    int res = scanf_s("%d", &size);

    Board table = init(size, 50);

    int isPlaying = 1;
    
    while(isPlaying == 1)
    {
        int x;
        int y;
        int res = scanf_s("%d%d", &x, &y);
        reveal(&table, x, y);
        if (table.grid[x + y*table.size].content == 9) {
            printf("c'est lose\n");
            isPlaying = 0;
        }
        displayBoard(table);
    }

    return 0;
}

void displayBoard(Board oBoard) {
    for (int i = 0; i < oBoard.size; i++) {
        for (int j = 0; j < oBoard.size; j++) {
            if (oBoard.grid[i * oBoard.size + j].isVisible == 0) {
                printf("H");
            }
            else {
                printf("%d", oBoard.grid[i * oBoard.size + j].content);
            }
        }
        printf("\n");
    }
}

Board init(int size, int mines) {
    Board table;
    table.size = size;
    table.grid = (Case*)malloc(sizeof(Case) * size * size);

    for (int j = 0; j < table.size * table.size; j++) {
        table.grid[j].content = 0;         
        table.grid[j].isVisible = 0;
    };

     int r = time(NULL);
     while (mines > 0) {
         int x = abs(r % size);
         r *= 3; r += 7;
         int y = abs(r % size);
         r *= 3; r += 7;
         if (table.grid[x + y * table.size].content == 0) {
             table.grid[x + y * table.size].content = 9;
             mines -= 1;
         }
         printf("%d", mines);
     }
    
    return table;
}


void reveal(Board* table, int x, int y) {
    if (table->grid[x + y * table->size].content != 9 && table->grid[x + y * table->size].isVisible == 0) {
        table->grid[x + y * table->size].isVisible = 1;
        check(table, x, y);
        if (table->grid[x + y * table->size].content == 0) {
            for (int i = -1; i < 2; i++) {  
                if(x+i >=0 && x+i < table->size){
                    for (int j = -1; j < 2; j++) {
                        if(y+j >=0 && y+j < table->size){
                            if(table->grid[(x+i) + (y+j) * table->size].isVisible != 1){
                                reveal(table, x + i, y + j);
                            }
                        }
                    }
                }
            }
        }
        //return table;
    }
    else {
        //return table;
    };
}

void check(Board* table, int x, int y) {
    if (table->grid[x + y * table->size].content != 9)
    {
        for (int i = -1; i < 2; i++) {
            if (x + i >= 0 && x + i < table->size) {
                for (int j = -1; j < 2; j++) {
                    if (y + j >= 0 && y + j < table->size) {
                        if (table->grid[(x + i) + (y + j) * table->size].content == 9) {
                            table->grid[x + y * table->size].content += 1;
                        }
                    }
                }
            }
        }
    }
}