// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>

#include "headers\board.h"
#include "headers\msutils.h"

int ZQSDActionSelector(Board* oBoard);

void tmpFuncGetData(int* iGridLength, int* iDifficulty);
void tmpFuncGetControlMode(char* cZQSDControl);


int main()
void generateMines(Board* oBoard);
    int isPlaying = 1;
    int iGridLength, iDifficulty; //,iMinesAmount;
    tmpFuncGetData(&iGridLength, &iDifficulty);//,&iMinesAmount);
void displayMenu(MMado* menu);
void gameControl(SDL_Event* event, Board* table);


int main(int argc, char* argv[])
void generateMines(Board* oBoard);
void oddToEvenByLower(int* number);
void checkWin(Board* table, int x, int y, int* playing);
void displayUI(GMado game);
void displayMenu(MMado* menu);
void gameControl(SDL_Event* event, Board* table);


int main(int argc, char* argv[])
void generateMines(Board* oBoard);
void oddToEvenByLower(int* number);
void checkWin(Board* table, int x, int y, int* playing);
void displayUI(GMado game);
void displayMenu(MMado* menu);
void gameControl(SDL_Event* event, Board* table);


int main(int argc, char* argv[])
void generateMines(Board* oBoard);
void oddToEvenByLower(int* number);
void checkWin(Board* table, int x, int y, int* playing);
void displayUI(GMado game);
void displayMenu(MMado* menu);
void gameControl(SDL_Event* event, Board* table);


int main(int argc, char* argv[])
void generateMines(Board* oBoard);
void oddToEvenByLower(int* number);
void checkWin(Board* table, int x, int y, int* playing);
void displayUI(GMado game);
void displayMenu(MMado* menu);
void gameControl(SDL_Event* event, Board* table);


int main(int argc, char* argv[])
{
    int isPlaying = 1;
    int iGridLength, iDifficulty; //,iMinesAmount;
    tmpFuncGetData(&iGridLength, &iDifficulty);//,&iMinesAmount);

    Board oBoard;
    construct(&oBoard, iGridLength, round(iGridLength * iGridLength / iDifficulty /2));
    
    int (*pfnGetAction)(Board*);
    pfnGetAction = ZQSDActionSelector;


    int actionType;

    while (!isGameOver(&oBoard, oBoard.iCursorPosition[0], oBoard.iCursorPosition[1])) {
        //EVENTS
        actionType = pfnGetAction(&oBoard);

        //UPDATE
        if (actionType == 1) {
            revealCase(&oBoard, oBoard.iCursorPosition[0], oBoard.iCursorPosition[1]);
        }
        else if (actionType == 2) {
            setFlag(&oBoard, oBoard.iCursorPosition[0], oBoard.iCursorPosition[1]);
        }

        //DISPLAY
        system("CLS");
        displayBoard(oBoard);
    }

    if (isGameOver(&oBoard, oBoard.iCursorPosition[0], oBoard.iCursorPosition[1]) == 1) {
        printf("You Lost");
    }
    else {
        printf("You Won");
    }
    return 0;
}


int ZQSDActionSelector(Board* oBoard) {
    char cKeyPress = 'a';
    while (true) {
        system("CLS");
        displayBoard(*oBoard);
        cKeyPress = _getch();

        if (cKeyPress == 'z') {
            setCursorSinleAxis(oBoard, oBoard->iCursorPosition[1] - 1, 1);
        }
        else if (cKeyPress == 'q') {
            setCursorSinleAxis(oBoard, oBoard->iCursorPosition[0] - 1, 0);
        }
        else if (cKeyPress == 's') {
            setCursorSinleAxis(oBoard, oBoard->iCursorPosition[1] + 1, 1);
        }
        else if (cKeyPress == 'd') {
            setCursorSinleAxis(oBoard, oBoard->iCursorPosition[0] + 1, 0);
        }
        else if (cKeyPress == '1') {
            return 1;
        }
        else if (cKeyPress == '2') {
            return 2;
        }
    }
}


void tmpFuncGetData(int* iGridLength, int* iDifficulty) {
    printf("Enter the length of the grid: ");
    getInput(iGridLength);
    while (*iGridLength < 2) {
        printf("The length of the grid has to be longer than 2: ");
        getInput(iGridLength);
    }

    printf("1 = Easy, 2 = Normal, 3 = Hard\nChoose a difficulty: ");
    getInput(iDifficulty);
    while (*iDifficulty != 1 && *iDifficulty != 2 && *iDifficulty != 3)
    {
        printf("1 = Easy, 2 = Normal, 3 = Hard\nPlease enter an integer between 1/2/3: ");
        getInput(iDifficulty);
    }
    *iDifficulty = 6 / *iDifficulty;

    //printf("Enter the amount of mines present on the grid : ");
    //getInput(&iMinesAmount);
    //while (iMinesAmount >= iGridLength * iGridLength && iMinesAmount >= 1) {
    //    printf("The mines amount has to be smaller than the amount of cases : ");
    //    getInput(&iMinesAmount);
    //}
}

void tmpFuncGetControlMode(char* cZQSDControl) {
    printf("Do you want to play with Z/Q/S/D controls ? (y/n) : ");
    clearSTDIN();
    scanf_s("%c", cZQSDControl);
    while (*cZQSDControl != 'y' && *cZQSDControl != 'n')
    {
        printf("Please enter \"y\" for Yes or \"n\" for No :");
        clearSTDIN();
        scanf_s("%c", cZQSDControl);
    }
}

