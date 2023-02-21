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
    Case grid[15][15];
    int size;
} Board;


Board init(int size);
void displayBoard(Board oBoard);
Board reveal(Board table, int x, int y);
int check(Board table, int x, int y);

int main()
{

    Board table = init(15);
    int isPlaying = 1;
    
    while(isPlaying == 1)
    {
        int x;
        int y;
        int res = scanf_s("%d%d", &x, &y);
        table = reveal(table, x, y);
        if (table.grid[y][x].content == 9) {
            printf("c'est lose");
            isPlaying = 0;
        }
        displayBoard(table);
    }

}

void displayBoard(Board oBoard) {
    for (int i = 0; i < oBoard.size; i++) {
        for (int j = 0; j < oBoard.size; j++) {
            if (oBoard.grid[i][j].isVisible == 0) {
                printf("H");
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
    int r = time(NULL);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if( r % 6 == 0){ table.grid[i][j].content = 9;}
            else{ table.grid[i][j].content = 0; }            
            table.grid[i][j].isVisible = 0;
            r += 7; r *= 3;
        }
    };
    
    return table;
}


Board reveal(Board table, int x, int y) {
    if (table.grid[y][x].content != 9 && table.grid[y][x].isVisible == 0) {
        table.grid[y][x].isVisible = 1;
        table.grid[y][x].content = check(table, x, y);
        if (table.grid[y][x].content == 0) {
            for (int i = -1; i < 2; i++) {  
                if(x+i >=0 && x+i < table.size){
                    for (int j = -1; j < 2; j++) {
                        if(y+j >=0 && y+j < table.size){
                            if(table.grid[y+j][x+i].isVisible != 1){
                                table = reveal(table, x + i, y + j);
                            }
                        }
                    }
                }
            }
        }
        return table;
    }
    else {
        return table;
    };
}

int check(Board table, int x, int y) {
    int upState = 0;
    if (table.grid[y][x].content != 9)
    {
        for (int i = -1; i < 2; i++) {
            if (x + i >= 0 && x + i < table.size) {
                for (int j = -1; j < 2; j++) {
                    if (y + j >= 0 && y + j < table.size) {
                        if (table.grid[y + j][x + i].content == 9) {
                            upState += 1;
                        }
                    }
                }
            }
        }
    }
    return upState;
}