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

/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

//#include <stdio.h>
//
//enum shapes { CIRCLE, RECTANGLE, SQUARE };
//
//// #define SCREEN_HEAD                 \
////         int i;                      \
////         enum shapes type;           \
////         char name[20]               \
////         double (*area)(void* this)  \
////         double (*perimeter)(void* this)  \
//
//typedef struct Square {
//    int id;
//    enum shapes type;
//    char name[20];
//    double (*area)(void* this);
//    double (*perimeter)(void* this);
//    double s;
//} Square;
//
//double s_area(void* this) {
//    Square* me = (Square*)this;
//    return me->s * me->s;
//}
//
//double s_perimeter(void* this) {
//    Square* me = (Square*)this;
//    return me->s * 4.0;
//}
//
//typedef struct Circle {
//    int id;
//    enum shapes type;
//    char name[20];
//    double (*area)(void* this);
//    double (*perimeter)(void* this);
//    double r;
//} Circle;
//
//double c_area(void* this) {
//    Circle* me = (Circle*)this;
//    return me->r * me->r * 3.14;
//}
//
//double c_perimeter(void* this) {
//    Circle* me = (Circle*)this;
//    return 2 * me->r * 3.14;
//}
//
//
//int main()
//{
//
//    Square square = { 1, SQUARE, "square", &s_area, &s_perimeter, 2 };
//    Circle circle = { 2, CIRCLE, "circle", &c_area, &c_perimeter,4 };
//    printf("Hello World\n");
//    printf("Square : id=%d, type=%d, name=%s, area=%.1f, perimeter=%.1f\n", square.id, square.type, square.name, square.area(&square), square.perimeter(&square));
//    printf("Circle : id=%d, type=%d, name=%s, area=%.1f, perimeter=%.1f\n", circle.id, circle.type, circle.name, circle.area(&circle), circle.perimeter(&circle));
//
//    return 0;
//}
