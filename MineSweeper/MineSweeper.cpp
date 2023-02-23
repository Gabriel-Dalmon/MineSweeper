// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

typedef struct Case {
    int content;
    int isVisible; // 1 = visible, 0 = hidden;
    int indicator;
    int flag = 0; //1 = drapeau, 0 = pas de drapeau

} Case;

typedef struct Board {
    Case* grid;
    int size;
    int remaining;
} Board;

Board init(int size, int mines);
void displayBoard(Board oBoard);
void reveal(Board* table, int x, int y);
void check(Board* table, int x, int y);
void setFlag(Board* table, int x, int y);

int main()
{
    int size;
    printf("Entrez une taille de grille : ");
    int resOne = scanf_s("%d", &size);

    Board table = init(size, 50);

    int isPlaying = 1;
    
    while(isPlaying == 1)
    {
        char flag;
        printf("flag ? (y / n)");
        int resTwo = scanf_s(" %c", &flag, 1);

        int x;
        int y;
        int resThree = scanf_s("%d%d", &x, &y);

        if(flag == 'n')
        {
            reveal(&table, x, y);
            if (table.grid[x + y * table.size].content == 9) {
                printf("c'est lose\n");
                isPlaying = 0;
            }
            else if (table.remaining == 0) {
                isPlaying = 0;
                printf("you won, congrats boy");
            }
        }
        else if (flag == 'y')
        {
            setFlag(&table, x, y);
        }
        else {
            printf("fais un effort mon reuf\n");
        }


        displayBoard(table);
            
    }

    return 0;
}

void displayBoard(Board oBoard) {
    for (int i = 0; i < oBoard.size; i++) {
        for (int j = 0; j < oBoard.size; j++) {
            if (oBoard.grid[i * oBoard.size + j].flag == 1) {
                printf("F");
            }
            else if (oBoard.grid[i * oBoard.size + j].isVisible == 0) {
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
    //Case* remaining = (Case*)malloc(sizeof(Case) * mines);
    table.size = size;
    table.grid = (Case*)malloc(sizeof(Case) * size * size);
    table.remaining = size * size - mines;

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
        table->remaining -= 1;
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


void setFlag (Board* table, int x, int y) {
    table->grid[(x + y * table->size)].flag = 1;
}