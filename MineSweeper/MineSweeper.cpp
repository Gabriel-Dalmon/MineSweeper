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

Case* getCaseByXY(Board* oBoard, int x, int y);
void setFlag(Board* oBoard, int x, int y);
void incrementAdjMinesAmount(Board* oBoard, int x, int y);
void setMine(Board* oBoard, int x, int y);

void revealCase(Board* oBoard, int x, int y);
int isGameOver(Board* oBoard, int x, int y);

void displayBoard(Board oBoard);

void setCursorSinleAxis(Board* oBoard, int dest, int axis);
int isCoordInGrid(int* iGridLength, int x, int y);

void oddToEvenByLower(int* number);
void getInput(int* dest);
void clearSTDIN();

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

void construct(Board* oBoard, int iGridLength, int iMinesAmount) {
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

                /*oBoard->grid[freeCases[randomIndex] + freeCases[randomIndex + 1] * oBoard->iGridLength].iContent = 9;
                oBoard->grid[freeCases[randomIndex] + freeCases[randomIndex + 1] * oBoard->iGridLength].isVisible = 1;*/
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
        oBoard->remaining -= 1;
        if (getCaseByXY(oBoard, x, y)->iContent == 0) {
            for (int i = -1; i < 2; i++) {  //to do : double loop function to get adjacent cases
                for (int j = -1; j < 2; j++) {
                    printf("Loop : %d|%d\n", j, i);
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

/*
* Utils
*/
void getInput(int* dest) {
    int res = scanf_s("%d", dest);
    while (res != 1) {
        clearSTDIN();
        printf("The input has to be an integer: ");
        res = scanf_s("%d", dest);
    }
}

void clearSTDIN() {
    while (getchar() != '\n');
}

void oddToEvenByLower(int* number) {
    if (*number % 2 == 1) {
        (*number)--;
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
