// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>

#include "board.h"
#include "msutils.h"

//int consoleCoordsSelector(Board* oBoard);
int ZQSDActionSelector(Board* oBoard);

void tmpFuncGetData(int* iGridLength, int* iDifficulty);
void tmpFuncGetControlMode(char* cZQSDControl);


int main()
{
    int isPlaying = 1;
    int iGridLength, iDifficulty; //,iMinesAmount;
    tmpFuncGetData(&iGridLength, &iDifficulty);//,&iMinesAmount);

    Board oBoard;
    construct(&oBoard, iGridLength, round(iGridLength * iGridLength / iDifficulty));
    
    //char cZQSDControl;
    //tmpFuncGetControlMode(&cZQSDControl);
    
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

    /*if(false)
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

            while (res != 2 || 0 > x || x >= iGridLength || 0 > y || y >= iGridLength) {
                printf("choisissez les coordonnées (x puis y)");
                while (getchar() != '\n' && getchar() != EOF) {
                    int ch = getchar();
                }
                res = scanf_s(" %d %d", &x, &y);
            }



            if (flag == 'n')
            {
                revealCase(&oBoard, x, y);
                isGameOver(&oBoard, x, y, &isPlaying);
            }
            else
            {
                setFlag(&oBoard, x, y);
            }


            displayBoard(oBoard);

            system("CLS");
        }
    }   */
    return 0;
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



//init la fenêtre = fonction pointer pour afficher le contenu de la fenêtre, gestion des évènements
//while
//ptnFunctionEventController(fenêtre,event.type)
// update fenêtre
//animationsHandler()
//displayContent(fenêtre)

//struct Board
//struct Menu
//struct Button {function pointer}

//fenêtre(type=Menu) Menu menu
//fenêtre(type=Game) Board board
// 
//  #define WINDOWS_HEAD
//          type
//          eventController
//          animationsHandler
// 
// struct Window
// type
// eventController
// content = &Menu
// 
// void (*revealCase)(x,y)
// 
// for
// for 
// Case.contnet = 9
// Case.revealCase = revealCaseMine
// 
// Menu menu;
// 
// Mado mado;
// mado.type = GAME;
// mado.content = Board board
// mado.display = displayMenu
// 
// 
// *mado.display(mado)
// 
// displayMenu(mado){
// mado.content displayed this way
// }
// 
// // displayGame(mado){
// mado.content displayed differently
// }
// 
// 
// struct MADO_HEAD {
//  int a;
//  Case* grid;
//  void (*function)(void* this);
// }
// 
// MADO.HEAD.function(MADOHEAD)
// 
//pas de ptnFunction mais surcharge de la fonction display
