// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>

typedef struct Case {
    int content;
    int isVisible; // 1 = visible, 0 = hidden;
    int indicator;
    int flag = 0; //1 = drapeau, 0 = pas de drapeau
    int current = 0; // position du joueur : si 1, le joueur est ici

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
void OddToEvenByLower(int* number);
void checkWin(Board* table, int x, int y, int* playing);


int main()
{
    int size;
    printf("Entrez une taille de grille : ");
    int res = scanf_s("%d", &size);

    int difficultie = 0;
    while (difficultie != 1 && difficultie !=2 && difficultie != 3)
    {
        printf("difficulté ? (1/2/3)");
        res = scanf_s("%d", &difficultie);
    }
    difficultie = 6 / difficultie;

    char zqsd = 'o';
    while(zqsd !='y' && zqsd != 'n')
    {
        printf("mode zqsd ? (y/n) ");
        res = scanf_s(" %c", &zqsd, 1);
    }

    Board table = init(size, 30); //round(size/difficultie));

    int isPlaying = 1;

    system("CLS");

    if(zqsd=='y')//
    {
        int position[2];
        position[0] = 0;
        position[1] = 0;
        table.grid[0].current = 1;
        displayBoard(table);

        while (isPlaying == 1)
        {


            system("CLS");
            displayBoard(table);

            char move = _getch();

            table.grid[position[0] + size * position[1]].current = 0;

            if (move == 'z') { if (position[1] > 0) {position[1] --; } }
            else if (move == 'q') { if (position[0]%size > 0) { position[0] --; } }
            else if (move == 's') { if (position[1] < size - 1){ position[1] ++; } }
            else if (move == 'd') { if (position[0] % size < size - 1) { position[0] ++; } }
            else if (move == '2') { setFlag(&table, position[0], position[1]); }
            else if (move == '1') {
                reveal(&table, position[0], position[1]);
                checkWin(&table, position[0], position[1], &isPlaying);
            }

            

            table.grid[position[0] + size * position[1]].current = 1;

        }
    }
    else
    {
        while (isPlaying == 1)
        {
            char flag = 'o';

            while (flag != 'y' && flag != 'n') {
                printf("flag ? (y / n)");
                res = scanf_s(" %c", &flag, 1);
            }



            int x = -1;
            int y = -1;
            res = 0;

            while (res != 2 || 0 > x || x >= size || 0 > y || y >= size) {
                printf("choisissez les coordonnées (x puis y)");
                while (getchar() != '\n' && getchar() != EOF) {
                    int ch = getchar();
                }
                res = scanf_s(" %d %d", &x, &y);
            }



            if (flag == 'n')
            {
                reveal(&table, x, y);
                checkWin(&table, x, y, &isPlaying);
            }
            else
            {
                setFlag(&table, x, y);
            }


            displayBoard(table);

            system("CLS");
        }
    }      
}

void displayBoard(Board oBoard) {
    for (int i = 0; i < oBoard.size; i++) {
        for (int j = 0; j < oBoard.size; j++) {
            if(oBoard.grid[i * oBoard.size + j].current == 1)
            {
                if (oBoard.grid[i * oBoard.size + j].flag == 1) {
                    printf("\x1b[46mF\033[0;37m ");
                }
                else if (oBoard.grid[i * oBoard.size + j].isVisible == 0) {
                    printf("\x1b[46mX\033[0;37m ");
                }
                else {
                    printf("\x1b[46m%d\033[0;37m ", oBoard.grid[i * oBoard.size + j].content);
                }
            }
            else {
                if (oBoard.grid[i * oBoard.size + j].flag == 1) {
                    printf("\033[0;32mF\033[0;37m ");
                }
                else if (oBoard.grid[i * oBoard.size + j].isVisible == 0) {
                    printf("\033[0; 32mX\033[0;37m ");
                }
                else if (oBoard.grid[i * oBoard.size + j].content == 0){ // on sait que la case est visible
                    printf("  ");
                }
                else {
                    printf("\033[0;31m%d\033[0;37m ", oBoard.grid[i * oBoard.size + j].content);
                }
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
     while (iMinesAmount > 0) {
         i++;
         int x = abs(r % size);
         r *= time(NULL) % 9; r += 1;
         int y = abs(r % size);
         r *= time(NULL) % 9;
         if (table.grid[x + y * table.size].content == 0) {
             table.grid[x + y * table.size].content = 9;
             iMinesAmount -= 1;
         }
     }
     generateMines(&table);
     displayBoard(table);
    return table;
}

void generateMines(Board* oBoard) {
    int iFreeCasesLength = oBoard->size * oBoard->size * 2;
    int* freeCases = (int*)malloc(sizeof(int) * iFreeCasesLength);
    
    for (int i = 0; i < oBoard->size; i++) {
        for (int j = 0; j < oBoard->size; j++) {
            freeCases[i * 2 + j * 2] = i;
            freeCases[i * 2 + j * 2 + 1] = j;
            printf("(%d|", freeCases[i * 2 + j * 2]);
            printf("%d)\n", freeCases[i * 2 + j * 2 + 1]);
        }
    }

    int* variable = (int*)realloc(freeCases, sizeof(int) * iFreeCasesLength - 2);
    if (variable != NULL) {
        freeCases = variable;
        iFreeCasesLength -= 2;
    }

    printf("\n\nRealocated\n\n");
    for (int i = 0; i < oBoard->size; i++) {
        for (int j = 0; j < oBoard->size; j++) {
            if (i != oBoard->size - 1 || j != oBoard->size - 1) {
                freeCases[i * 2 + j * 2] = i;
                freeCases[i * 2 + j * 2 + 1] = j;
                printf("(%d|", freeCases[i * 2 + j * 2]);
                printf("%d)\n", freeCases[i * 2 + j * 2 + 1]);
            }

        }
    }

    printf("Mines amount : %d", oBoard->iMinesAmount);
    int rand = time(NULL);
    for (int i = 0; i < 1; i++) {
        int randFreeCaseIndex = abs(rand % iFreeCasesLength);
        OddToEvenByLower(&randFreeCaseIndex);
        rand = (rand + 1) * 7;
    }
    free(freeCases);
}

void OddToEvenByLower(int* number) {
    if (*number % 2 == 1) {
        (*number)--;
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
    if (table->grid[(x + y * table->size)].flag == 1) {
        table->grid[(x + y * table->size)].flag = 0;
    }
    else {
        table->grid[(x + y * table->size)].flag = 1;
    }
}

void checkWin(Board* table, int x, int y, int* playing) {
    if (table->grid[x + y * table->size].content == 9)
    {
        printf("c'est lose\n");
        *playing = 0;
    }
    else if (table->remaining == 0)
    {
        printf("you won, congrats boy\n");
        *playing = 0;
    }
}