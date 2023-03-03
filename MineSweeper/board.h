#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED



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

#endif