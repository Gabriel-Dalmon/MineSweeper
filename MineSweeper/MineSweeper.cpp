// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>

typedef struct Case {
    int iContent; // 9 = mines, 0-8 = amount of adjacent mines
    int isVisible; // 1 = visible, 0 = hidden;
    int isFlag; //1 = drapeau, 0 = pas de drapeau
} Case;

typedef struct Board {
    Case* grid;
    int iGridLength;
    int remaining;
    int iMinesAmount;
    int iCursorPosition[2];
} Board;


void construct(Board* oBoard, int iGridLength, int minesAmount);
void generateMines(Board* oBoard);

void setFlag(Board* oBoard, int x, int y);

void reveal(Board* oBoard, int x, int y);
void check(Board* oBoard, int x, int y);
int isWinning(Board* oBoard, int x, int y);

void displayBoard(Board oBoard);



void oddToEvenByLower(int* number);
void getIntInput(int* dest);
void getCharInput(char* dest);
void clearSTDIN();

//int consoleCoordsSelector(Board* oBoard);
int ZQSDActionSelector(Board* oBoard);

void tmpFuncGetData(int* iGridLength, int* iDifficulty);
void tmpFuncGetControlMode(char* cZQSDControl);

int main()
{
    int isPlaying = 1;
    int iGridLength, iDifficulty;

    tmpFuncGetData(&iGridLength, &iDifficulty);
    //int iMinesAmount = 0;
    //printf("Enter the amount of mines present on the grid : ");
    //getIntInput(&iMinesAmount);
    //while (iMinesAmount >= iGridLength * iGridLength && iMinesAmount >= 1) {
    //    printf("The mines amount has to be smaller than the amount of cases : ");
    //    getIntInput(&iMinesAmount);
    //}

    Board oBoard;
    construct(&oBoard, iGridLength, round(iGridLength * iGridLength / iDifficulty));
    

    char cZQSDControl;
    //tmpFuncGetControlMode(&cZQSDControl);
    
    int (*pfnGetAction)(Board*);
    pfnGetAction = ZQSDActionSelector;

    int actionType;
    while (isPlaying == 1) {
        system("CLS");
        displayBoard(oBoard);
        actionType = pfnGetAction(&oBoard);
        if (actionType == 1) { /* iType = 1 : The player reveals a new case */
            reveal(&oBoard, oBoard.iCursorPosition[0], oBoard.iCursorPosition[1]);
            isWinning(&oBoard, oBoard.iCursorPosition[0], oBoard.iCursorPosition[1]);
        }
        else if (actionType == 2) { /* iType = 2 : The player sets a flag */
            setFlag(&oBoard, oBoard.iCursorPosition[0], oBoard.iCursorPosition[1]);
        }
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
                reveal(&oBoard, x, y);
                isWinning(&oBoard, x, y, &isPlaying);
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




void displayBoard(Board oBoard) {
    for (int i = 0; i < oBoard.iGridLength; i++) {
        for (int j = 0; j < oBoard.iGridLength; j++) {
            if(j == oBoard.iCursorPosition[0] && i == oBoard.iCursorPosition[1])
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
                else if (oBoard.grid[i * oBoard.iGridLength + j].iContent == 0){ // on sait que la case est visible
                    printf("  ");
                }
                else {
                    printf("\033[0;31m%d\033[0;37m ", oBoard.grid[i * oBoard.iGridLength + j].iContent);
                }
            }
        }
        printf("\n");
    }
    printf("%d|%d\n", oBoard.iCursorPosition[0], oBoard.iCursorPosition[1]);
}

void setCursorSinleAxis(Board* oBoard, int dest, int axis) {
    if (axis == 0) {
        if (dest >= 0 && dest <= oBoard->iGridLength) {
            oBoard->iCursorPosition[axis] = dest;
        }
    } else if (dest % oBoard->iGridLength >= 0 && dest % oBoard->iGridLength <= oBoard->iGridLength) {
        oBoard->iCursorPosition[axis] = dest;
    }
}

int ZQSDActionSelector(Board* oBoard) {
    char cKeyPress = 'a';
    while (true) {
        system("CLS");
        displayBoard(*oBoard);
        cKeyPress = _getch();

        if (cKeyPress == 'z') {
            setCursorSinleAxis(oBoard, oBoard->iCursorPosition[1] - 1, 1);
        } else if (cKeyPress == 'q') {
            setCursorSinleAxis(oBoard, oBoard->iCursorPosition[0] - 1,0);
        } else if (cKeyPress == 's') {
            setCursorSinleAxis(oBoard, oBoard->iCursorPosition[1] + 1, 1);
        } else if (cKeyPress == 'd') {
            setCursorSinleAxis(oBoard, oBoard->iCursorPosition[0] + 1, 0);
        } else if (cKeyPress == '1') {
            return 1;
        } else if (cKeyPress == '2') {
            return 2;
        }
    }
}

void construct(Board* oBoard, int iGridLength, int iMinesAmount) {
    oBoard->iGridLength = iGridLength;
    oBoard->grid = (Case*)malloc(sizeof(Case) * oBoard->iGridLength * oBoard->iGridLength);
    oBoard->iMinesAmount = iMinesAmount;
    oBoard->remaining = oBoard->iGridLength * oBoard->iGridLength - oBoard->iMinesAmount;
    oBoard->iCursorPosition[0] = 0;
    oBoard->iCursorPosition[1] = 0;

    for (int j = 0; j < oBoard->iGridLength * oBoard->iGridLength; j++) {
        //oBoard->grid[j] = { 0, 0, 0 };
        oBoard->grid[j].iContent = 0;
        oBoard->grid[j].isVisible = 0;
        oBoard->grid[j].isFlag = 0;
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
                oBoard->grid[freeCases[randomIndex] + freeCases[randomIndex + 1] * oBoard->iGridLength].iContent = 9;
                oBoard->grid[freeCases[randomIndex] + freeCases[randomIndex + 1] * oBoard->iGridLength].isVisible = 1;
                freeCases[randomIndex] = tmpLastFreeCase[0];
                freeCases[randomIndex + 1] = tmpLastFreeCase[1];
            }
        }
        else {
            //int r = time(NULL);
            //int i = 0;
            //while (iMinesAmount > 0) {
            //    i++;
            //    int x = abs(r % iGridLength);
            //    r *= time(NULL) % 9; r += 1;
            //    int y = abs(r % iGridLength);
            //    r *= time(NULL) % 9;
            //    if (oBoard.grid[x + y * oBoard.iGridLength].iContent == 0) {
            //        oBoard.grid[x + y * oBoard.iGridLength].iContent = 9;
            //        iMinesAmount -= 1;
            //    }
            //}
            break;
        }
    }
    free(freeCases);
}



void reveal(Board* oBoard, int x, int y) {
    if (oBoard->grid[x + y * oBoard->iGridLength].iContent != 9 && oBoard->grid[x + y * oBoard->iGridLength].isVisible == 0) {
        oBoard->grid[x + y * oBoard->iGridLength].isVisible = 1;
        oBoard->remaining -= 1;
        check(oBoard, x, y);
        if (oBoard->grid[x + y * oBoard->iGridLength].iContent == 0) {
            for (int i = -1; i < 2; i++) {  
                if(x+i >=0 && x+i < oBoard->iGridLength){
                    for (int j = -1; j < 2; j++) {
                        if(y+j >=0 && y+j < oBoard->iGridLength){
                            if(oBoard->grid[(x+i) + (y+j) * oBoard->iGridLength].isVisible != 1){
                                reveal(oBoard, x + i, y + j);
                            }
                        }
                    }
                }
            }
        }
    };
}

void check(Board* oBoard, int x, int y) {
    if (oBoard->grid[x + y * oBoard->iGridLength].iContent != 9)
    {
        for (int i = -1; i < 2; i++) {
            if (x + i >= 0 && x + i < oBoard->iGridLength) {
                for (int j = -1; j < 2; j++) {
                    if (y + j >= 0 && y + j < oBoard->iGridLength) {
                        if (oBoard->grid[(x + i) + (y + j) * oBoard->iGridLength].iContent == 9) {
                            oBoard->grid[x + y * oBoard->iGridLength].iContent += 1;
                        }
                    }
                }
            }
        }
    }
}


void setFlag (Board* oBoard, int x, int y) {
    if (oBoard->grid[(x + y * oBoard->iGridLength)].isFlag == 1) {
        oBoard->grid[(x + y * oBoard->iGridLength)].isFlag = 0;
    }
    else {
        oBoard->grid[(x + y * oBoard->iGridLength)].isFlag = 1;
    }
}

int isWinning(Board* oBoard, int x, int y) {
    if (oBoard->grid[x + y * oBoard->iGridLength].iContent == 9)
    {
        printf("c'est lose\n");
        return 0;
    }
    else if (oBoard->remaining == 0)
    {
        printf("you won, congrats boy\n");
        return 0;
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

void tmpFuncGetData(int* iGridLength, int* iDifficulty) {
    printf("Enter the length of the grid: ");
    getIntInput(iGridLength);
    while (*iGridLength < 2) {
        printf("The length of the grid has to be longer than 2: ");
        getIntInput(iGridLength);
    }

    printf("1 = Easy, 2 = Normal, 3 = Hard\nChoose a difficulty: ");
    getIntInput(iDifficulty);
    while (*iDifficulty != 1 && *iDifficulty != 2 && *iDifficulty != 3)
    {
        printf("1 = Easy, 2 = Normal, 3 = Hard\nPlease enter an integer between 1/2/3: ");
        getIntInput(iDifficulty);
    }
    *iDifficulty = 6 / *iDifficulty;
}

void tmpFuncGetControlMode(char* cZQSDControl) {
    printf("Do you want to play with Z/Q/S/D controls ? (y/n) ");
    getCharInput(cZQSDControl);
    while (*cZQSDControl != 'y' && *cZQSDControl != 'n')
    {
        printf("Please enter \"y\" for Yes or \"n\" for No");
        getCharInput(cZQSDControl);
    }
}