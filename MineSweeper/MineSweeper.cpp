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
    int iGridLength;
    int remaining;
    int iMinesAmount;
} Board;


Board init(int iLength, int mines);
void displayBoard(Board oBoard);
void reveal(Board* table, int x, int y);
void check(Board* table, int x, int y);
void setFlag(Board* table, int x, int y);
void generateMines(Board* oBoard);
void oddToEvenByLower(int* number);
void isWinning(Board* table, int x, int y, int* playing);
void getIntInput(int* dest);
void getCharInput(char* dest);
void clearSTDIN();


int main()
{
    int isPlaying = 1;
    Board oBoard;
    construct(&oBoard);


    char cZQSDControl = 'x';
    printf("Do you want to play with Z/Q/S/D controls ? (y/n) ");
    getCharInput(&cZQSDControl);
    while(cZQSDControl !='y' && cZQSDControl != 'n')
    {
        printf("Please enter \"y\" for Yes or \"n\" for No");
        getCharInput(&cZQSDControl);
    }
    
    if (cZQSDControl == 'y') {
        void (*getCoordinates)() = getCoordinatesZQSD();
    }

    Board oBoard = init(iGridLength, round(iGridLength / iDifficulty));

    while (isPlaying == 1) {
        system("CLS");
        coords = getCoordinates();
        reveal(oBoard, coords[0], coords[1]);
        isWinning(oBoard, coords[0], coords[1]);
        displayBoard(table);
    }

    if(cZQSDControl=='y')//
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

            table.grid[position[0] + iLength * position[1]].current = 0;

            if (move == 'z') { if (position[1] > 0) {position[1] --; } }
            else if (move == 'q') { if (position[0]%iLength > 0) { position[0] --; } }
            else if (move == 's') { if (position[1] < iLength - 1){ position[1] ++; } }
            else if (move == 'd') { if (position[0] % iLength < iLength - 1) { position[0] ++; } }
            else if (move == '2') { setFlag(&table, position[0], position[1]); }
            else if (move == '1') {
                reveal(&table, position[0], position[1]);
                isWinning(&table, position[0], position[1], &isPlaying);
            }

            

            table.grid[position[0] + iLength * position[1]].current = 1;

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

            while (res != 2 || 0 > x || x >= iLength || 0 > y || y >= iLength) {
                printf("choisissez les coordonnées (x puis y)");
                while (getchar() != '\n' && getchar() != EOF) {
                    int ch = getchar();
                }
                res = scanf_s(" %d %d", &x, &y);
            }



            if (flag == 'n')
            {
                reveal(&table, x, y);
                isWinning(&table, x, y, &isPlaying);
            }
            else
            {
                setFlag(&table, x, y);
            }


            displayBoard(table);

            system("CLS");
        }
    }   
    return 0;
}

void displayBoard(Board oBoard) {
    for (int i = 0; i < oBoard.iLength; i++) {
        for (int j = 0; j < oBoard.iLength; j++) {
            if(oBoard.grid[i * oBoard.iLength + j].current == 1)
            {
                if (oBoard.grid[i * oBoard.iLength + j].flag == 1) {
                    printf("\x1b[46mF\033[0;37m ");
                }
                else if (oBoard.grid[i * oBoard.iLength + j].isVisible == 0) {
                    printf("\x1b[46mX\033[0;37m ");
                }
                else {
                    printf("\x1b[46m%d\033[0;37m ", oBoard.grid[i * oBoard.iLength + j].content);
                }
            }
            else {
                if (oBoard.grid[i * oBoard.iLength + j].flag == 1) {
                    printf("\033[0;32mF\033[0;37m ");
                }
                else if (oBoard.grid[i * oBoard.iLength + j].isVisible == 0) {
                    printf("\033[0; 32mX\033[0;37m ");
                }
                else if (oBoard.grid[i * oBoard.iLength + j].content == 0){ // on sait que la case est visible
                    printf("  ");
                }
                else {
                    printf("\033[0;31m%d\033[0;37m ", oBoard.grid[i * oBoard.iLength + j].content);
                }
            }
        }
        printf("\n");
    }
}


void construct(Board* oBoard) {
    printf("Enter the length of the grid: ");
    getIntInput(&oBoard->iGridLength);
    while (oBoard->iGridLength < 2) {
        printf("The length of the grid has to be longer than 2: ");
        getIntInput(&oBoard->iGridLength);
    }

    int iMinesAmount = 0;
    //printf("Enter the amount of mines present on the grid : ");
    //getIntInput(&iMinesAmount);
    //while (iMinesAmount >= iGridLength * iGridLength && iMinesAmount >= 1) {
    //    printf("The mines amount has to be smaller than the amount of cases : ");
    //    getIntInput(&iMinesAmount);
    //}

    int iDifficulty = 0;
    printf("1 = Easy, 2 = Normal, 3 = Hard\nChoose a difficulty: ");
    getIntInput(&iDifficulty);
    while (iDifficulty != 1 && iDifficulty != 2 && iDifficulty != 3)
    {
        printf("1 = Easy, 2 = Normal, 3 = Hard\nPlease enter an integer between 1/2/3: ");
        getIntInput(&iDifficulty);
    }
    iDifficulty = 6 / iDifficulty;
}

Board init(int iLength, int iMinesAmount) {
    Board table;
    table.iLength = iLength;
    table.grid = (Case*)malloc(iLengthof(Case) * table.iLength * table.iLength);
    table.iMinesAmount = iMinesAmount;
    table.remaining = iLength * iLength - iMinesAmount;


    for (int j = 0; j < table.iLength * table.iLength; j++) {
        table.grid[j].content = 0;         
        table.grid[j].isVisible = 0;
    };

    
    for (int j = 0; j < table.iLength * table.iLength; j++) {

    }

     //int r = time(NULL);
     //int i = 0;
     //while (iMinesAmount > 0) {
     //    i++;
     //    int x = abs(r % iLength);
     //    r *= time(NULL) % 9; r += 1;
     //    int y = abs(r % iLength);
     //    r *= time(NULL) % 9;
     //    if (table.grid[x + y * table.iLength].content == 0) {
     //        table.grid[x + y * table.iLength].content = 9;
     //        iMinesAmount -= 1;
     //    }
     //}
     generateMines(&table);
     displayBoard(table);
    return table;
}

void generateMines(Board* oBoard) {
    int iFreeCasesLength = oBoard->iLength * oBoard->iLength * 2;
    int* freeCases = (int*)malloc(iLengthof(int) * iFreeCasesLength);
    
    for (int i = 0; i < oBoard->iLength; i++) {
        for (int j = 0; j < oBoard->iLength; j++) {
            freeCases[i * oBoard->iLength * 2 + j * 2] = i;
            freeCases[i * oBoard->iLength * 2 + j * 2 + 1] = j;
        }
    }

    int r = time(NULL);

    for (int i = 0; i < oBoard->iMinesAmount; i++) {
        int tmpLastFreeCase[2] = { freeCases[iFreeCasesLength - 2], freeCases[iFreeCasesLength - 1] };
        int* variable = (int*)realloc(freeCases, iLengthof(int) * iFreeCasesLength - 2);
        if (variable != NULL) {
            freeCases = variable;
            iFreeCasesLength -= 2;
            int randomIndex = r % iFreeCasesLength;
            oddToEvenByLower(&randomIndex);
            if (randomIndex != iFreeCasesLength - 1) {
                oBoard->grid[freeCases[randomIndex] + freeCases[randomIndex + 1] * oBoard->iLength].content = 9;
                oBoard->grid[freeCases[randomIndex] + freeCases[randomIndex + 1] * oBoard->iLength].isVisible = 1;
                freeCases[randomIndex] = tmpLastFreeCase[0];
                freeCases[randomIndex + 1] = tmpLastFreeCase[1];
            }
        }
    }
    free(freeCases);
}



void reveal(Board* table, int x, int y) {
    if (table->grid[x + y * table->iLength].content != 9 && table->grid[x + y * table->iLength].isVisible == 0) {
        table->grid[x + y * table->iLength].isVisible = 1;
        table->remaining -= 1;
        check(table, x, y);
        if (table->grid[x + y * table->iLength].content == 0) {
            for (int i = -1; i < 2; i++) {  
                if(x+i >=0 && x+i < table->iLength){
                    for (int j = -1; j < 2; j++) {
                        if(y+j >=0 && y+j < table->iLength){
                            if(table->grid[(x+i) + (y+j) * table->iLength].isVisible != 1){
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
    if (table->grid[x + y * table->iLength].content != 9)
    {
        for (int i = -1; i < 2; i++) {
            if (x + i >= 0 && x + i < table->iLength) {
                for (int j = -1; j < 2; j++) {
                    if (y + j >= 0 && y + j < table->iLength) {
                        if (table->grid[(x + i) + (y + j) * table->iLength].content == 9) {
                            table->grid[x + y * table->iLength].content += 1;
                        }
                    }
                }
            }
        }
    }
}


void setFlag (Board* table, int x, int y) {
    if (table->grid[(x + y * table->iLength)].flag == 1) {
        table->grid[(x + y * table->iLength)].flag = 0;
    }
    else {
        table->grid[(x + y * table->iLength)].flag = 1;
    }
}

void isWinning(Board* table, int x, int y, int* playing) {
    if (table->grid[x + y * table->iLength].content == 9)
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


void getIntInput(int* dest) {
    int res = scanf_s("%d", dest);
    while (res != 1) {
        clearSTDIN();
        printf("The input has to be an integer: ");
        res = scanf_s("%d", dest);
    }
}

void getCharInput(char* dest) {
    int res = scanf_s("%c", dest);
    while (res != 1) {
        clearSTDIN();
        printf("The input has to be a character: ");
        res = scanf_s("%c", dest);
    }
}

void clearSTDIN() {
    while ((getchar()) != '\n');
}

void oddToEvenByLower(int* number) {
    if (*number % 2 == 1) {
        (*number)--;
    }
}

