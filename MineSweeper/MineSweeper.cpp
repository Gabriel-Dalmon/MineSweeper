// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int iMinesAmount;
} Board;

Board init(int size, int mines);
void displayBoard(Board oBoard);
void reveal(Board* table, int x, int y);
void check(Board* table, int x, int y);
void setFlag(Board* table, int x, int y);
void generateMines(Board* oBoard);

int main()
{
    int size;
    printf("Entrez une taille de grille : ");
    int resOne = scanf_s("%d", &size);

    Board table = init(size, 30);

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

    free(table.grid);
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

Board init(int size, int iMinesAmount) {
    Board table;
    table.size = size;
    table.grid = (Case*)malloc(sizeof(Case) * table.size * table.size);
    table.iMinesAmount = iMinesAmount;
    table.remaining = size * size - iMinesAmount;


    for (int j = 0; j < table.size * table.size; j++) {
        table.grid[j].content = 0;         
        table.grid[j].isVisible = 0;
    };

    
    for (int j = 0; j < table.size * table.size; j++) {

    }

     int r = time(NULL);
     int i = 0;
     while (table.iMinesAmount > 0) {
         i++;
         int x = abs(r % size);
         r *= time(NULL) % 9; r += 1;
         int y = abs(r % size);
         r *= time(NULL) % 9;
         if (table.grid[x + y * table.size].content == 0) {
             table.grid[x + y * table.size].content = 9;
             table.iMinesAmount -= 1;
         }
         printf("Nombre d'itérations : %d\n", i);
     }
     
     displayBoard(table);
    return table;
}

void generateMines(Board* oBoard) {
    int* freeCases = (int*)malloc(sizeof(int) * oBoard->size * oBoard->size * 2);

    for (int i = 0; i < oBoard->iMinesAmount; i++) {
        int a;
    }

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