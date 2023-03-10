#ifndef MSLOGIC_H_INCLUDED
#define MSLOGIC_H_INCLUDED

/**
* Virtually represents a case in the MSBoard.
*/
typedef struct Case {
    int iContent; /**@var int iContent - 9 = mines, 0-8 = amount of adjacent mines */
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

void constructMSBoard(Board* oBoard, int iGridLength, int iMinesAmount);
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

#endif