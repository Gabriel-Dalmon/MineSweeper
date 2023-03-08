#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "headers\board.h"
#include "headers\msutils.h"

void constructMSBoard(Board* oBoard, int iGridLength, int iMinesAmount) {
    oBoard->iGridLength = iGridLength;
    oBoard->grid = (Case*)malloc(sizeof(Case) * oBoard->iGridLength * oBoard->iGridLength);
    oBoard->iMinesAmount = iMinesAmount;
    oBoard->remaining = oBoard->iGridLength * oBoard->iGridLength - oBoard->iMinesAmount;
    oBoard->iCursorPosition[0] = 0;
    oBoard->iCursorPosition[1] = 0;

    for (int j = 0; j < oBoard->iGridLength * oBoard->iGridLength; j++) {
        oBoard->grid[j] = { 0, 0, 0 };

    };

    generateMines(oBoard);
}

void generateMines(Board* oBoard) {
    int iFreeCasesLength = oBoard->iGridLength * oBoard->iGridLength * 2;
    int* freeCases = (int*)malloc(sizeof(int) * iFreeCasesLength);

    for (int i = 0; i < oBoard->iGridLength; i++) {
        for (int j = 0; j < oBoard->iGridLength; j++) {
            freeCases[i * oBoard->iGridLength * 2 + j * 2] = i;
            freeCases[i * oBoard->iGridLength * 2 + j * 2 + 1] = j;
        }
    }

    int r = time(NULL);

    for (int i = 0; i < oBoard->iMinesAmount; i++) {
        int tmpLastFreeCase[2] = { freeCases[iFreeCasesLength - 2], freeCases[iFreeCasesLength - 1] };
        int* variable = (int*)realloc(freeCases, sizeof(int) * iFreeCasesLength - 2);
        if (variable != NULL) {
            freeCases = variable;
            iFreeCasesLength -= 2;
            int randomIndex = r % iFreeCasesLength;
            oddToEvenByLower(&randomIndex);
            if (randomIndex != iFreeCasesLength - 1) {
                setMine(oBoard, freeCases[randomIndex], freeCases[randomIndex + 1]);
                freeCases[randomIndex] = tmpLastFreeCase[0];
                freeCases[randomIndex + 1] = tmpLastFreeCase[1];
            }
        }
        else {
            int r = time(NULL);
            int i = 0;
            while (oBoard->iMinesAmount > 0) {
                i++;
                int x = abs(r % oBoard->iGridLength);
                r *= time(NULL) % 9; r += 1;
                int y = abs(r % oBoard->iGridLength);
                r *= time(NULL) % 9;
                if (oBoard->grid[x + y * oBoard->iGridLength].iContent == 0) {
                    oBoard->grid[x + y * oBoard->iGridLength].iContent = 9;
                    oBoard->iMinesAmount -= 1;
                }
            }
            break;
        }
    }
    free(freeCases);
}

void setMine(Board* oBoard, int x, int y) {
    //sets a mine and increments the amount of adjacent mines on adjacent cases
    if (isCoordInGrid(&oBoard->iGridLength, x, y) && getCaseByXY(oBoard, x, y)->iContent != 9) {
        getCaseByXY(oBoard, x, y)->iContent = 9;
        incrementAdjMinesAmount(oBoard, x, y);
    }
}

void incrementAdjMinesAmount(Board* oBoard, int x, int y) {
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if (isCoordInGrid(&oBoard->iGridLength, j, i) && getCaseByXY(oBoard, j, i)->iContent != 9) {
                getCaseByXY(oBoard, j, i)->iContent++;
            }
        }
    }
}

void setFlag(Board* oBoard, int x, int y) {
    if (getCaseByXY(oBoard, x, y)->isVisible == 0) {
        if (oBoard->grid[(x + y * oBoard->iGridLength)].isFlag == 1) {
            oBoard->grid[(x + y * oBoard->iGridLength)].isFlag = 0;
        }
        else {
            oBoard->grid[(x + y * oBoard->iGridLength)].isFlag = 1;
        }
    }
}

void revealCase(Board* oBoard, int x, int y) {
    if (getCaseByXY(oBoard, x, y)->isVisible == 0) {
        getCaseByXY(oBoard, x, y)->isVisible = 1;
        getCaseByXY(oBoard, x, y)->isFlag = 0;
        oBoard->remaining -= 1;
        if (getCaseByXY(oBoard, x, y)->iContent == 0) {
            for (int i = -1; i < 2; i++) {  //to do : double loop function to get adjacent cases
                for (int j = -1; j < 2; j++) {
                    if (isCoordInGrid(&oBoard->iGridLength, x + j, y + i) && getCaseByXY(oBoard, x + j, y + i)->isVisible != 1) {
                        revealCase(oBoard, x + j, y + i);
                    }
                }
            }
        }
    }
}

int isGameOver(Board* oBoard, int x, int y) {
    if (getCaseByXY(oBoard, x, y)->iContent == 9 && getCaseByXY(oBoard, x, y)->isVisible)
    {
        return 1;
    }
    else if (oBoard->remaining == 0)
    {
        return 2;
    }
    else {
        return 0;
    }
}



void displayBoard(Board oBoard) {
    for (int i = 0; i < oBoard.iGridLength; i++) {
        for (int j = 0; j < oBoard.iGridLength; j++) {
            if (j == oBoard.iCursorPosition[0] && i == oBoard.iCursorPosition[1])
            {
                if (oBoard.grid[i * oBoard.iGridLength + j].isFlag == 1) {
                    printf("\x1b[46mF\033[0;37m ");
                }
                else if (oBoard.grid[i * oBoard.iGridLength + j].isVisible == 0) {
                    printf("\x1b[46mX\033[0;37m ");
                }
                else {
                    printf("\x1b[46m%d\033[0;37m ", oBoard.grid[i * oBoard.iGridLength + j].iContent);
                }
            }
            else {
                if (oBoard.grid[i * oBoard.iGridLength + j].isFlag == 1) {
                    printf("\033[0;32mF\033[0;37m ");
                }
                else if (oBoard.grid[i * oBoard.iGridLength + j].isVisible == 0) {
                    printf("\033[0; 32mX\033[0;37m ");
                }
                else if (oBoard.grid[i * oBoard.iGridLength + j].iContent == 0) { // on sait que la case est visible
                    printf("  ");
                }
                else {
                    printf("\033[0;31m%d\033[0;37m ", oBoard.grid[i * oBoard.iGridLength + j].iContent);
                }
            }
        }
        printf("\n");
    }
}

/*
* Board Utils
*/
void setCursorSinleAxis(Board* oBoard, int dest, int axis) {
    if (dest >= 0 && dest < oBoard->iGridLength) {
        oBoard->iCursorPosition[axis] = dest;
    }
}

int isCoordInGrid(int* iGridLength, int x, int y) {
    return x >= 0 && x < *iGridLength && y >= 0 && y < *iGridLength;
}

Case* getCaseByXY(Board* oBoard, int x, int y) {
    return &oBoard->grid[x + y * oBoard->iGridLength];
}
