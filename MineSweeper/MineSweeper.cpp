// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <windows.h>

#include "headers\board.h"
#include "headers\msutils.h"

enum SCREEN_TYPES {MAINMENU, MINESWEEPER};

#define SCREEN_HEAD                            \
        enum SCREEN_TYPES type; \
        void (*displayScreen)(void* this_t);    \
        void (*eventsHandler)(void* this_t);    \



typedef struct MSSDL_Ressources {
    SDL_Rect tile;
    SDL_Color fontColor;
    TTF_Font* font;
    SDL_Surface* message;
    char content[2];
    SDL_Texture* indicTile;
    SDL_Surface* flagImg;
    SDL_Texture* flagTexture;
} MSSDL_Ressources;

typedef struct ScreenMS {
    SCREEN_HEAD
    Board oBoard;
    MSSDL_Ressources SDLRessources;
};


void loadMSSDLRessources(MSSDL_Ressources* SDLRessources, SDL_Renderer* renderer) {
    SDLRessources->tile.w = SDLRessources->tile.h = 50;
    SDLRessources->font = TTF_OpenFont("fonts/ttf-bitstream-vera-1.10/Vera.ttf", 16);
    SDLRessources->flagImg = IMG_Load("img/good_flag.png");
    SDLRessources->flagTexture = SDL_CreateTextureFromSurface(renderer, SDLRessources->flagImg);
}

void tmpFuncGetData(int* iGridLength, int* iDifficulty);
void tmpFuncGetControlMode(char* cZQSDControl);

void displayUI(Board* oBoard, SDL_Window* window, SDL_Renderer* renderer, MSSDL_Ressources* ressources);
void eventHandler(SDL_Event* event, Board* oBoard);

int main(int argc, char* argv[])
{
    int isPlaying = 1;
    int iGridLength, iDifficulty; //,iMinesAmount;
    tmpFuncGetData(&iGridLength, &iDifficulty);//,&iMinesAmount);

    ScreenMS oScreen = { MINESWEEPER };
    construct(&oScreen.oBoard, iGridLength, round(iGridLength * iGridLength / iDifficulty / 2));
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Init();
    window = SDL_CreateWindow("MineSweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Création du renderer
    loadMSSDLRessources(&oScreen.SDLRessources, renderer);


    while (!isGameOver(&oScreen.oBoard, oScreen.oBoard.iCursorPosition[0], oScreen.oBoard.iCursorPosition[1])) {
        //EVENTS
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            eventHandler(&event, &oScreen.oBoard);
        }

        //DISPLAY
        displayUI(&oScreen.oBoard, window, renderer, &oScreen.SDLRessources);
    }

    if (isGameOver(&oScreen.oBoard, oScreen.oBoard.iCursorPosition[0], oScreen.oBoard.iCursorPosition[1]) == 1) {
        printf("You Lost");
    }
    else {
        printf("You Won");
    }
    return 0;
}



void displayUI(Board* oBoard, SDL_Window* window, SDL_Renderer* renderer, MSSDL_Ressources* ressources) {
    SDL_RenderClear(renderer);

    for (int i = 0; i < oBoard->iGridLength; i++) {
        for (int j = 0; j < oBoard->iGridLength; j++)
        {

            ressources->tile.x = j * 50;//{position x * la taille d'une case, position y * la taille d'une case, taille de la case (20 * 20)}
            ressources->tile.y = i * 50;//{position x * la taille d'une case, position y * la taille d'une case, taille de la case (20 * 20)}
            
            if (oBoard->grid[i * oBoard->iGridLength + j].isFlag == 1) {

                if ((i * oBoard->iGridLength + j) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 160, 0, 160, 255);
                }
                else { SDL_SetRenderDrawColor(renderer, 150, 0, 150, 255); }

                SDL_RenderFillRect(renderer, &ressources->tile);
                SDL_RenderCopy(renderer, ressources->flagTexture, NULL, &ressources->tile);


            }
            else if (oBoard->grid[i * oBoard->iGridLength + j].isVisible == 0) {


                if ((i * oBoard->iGridLength + j) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 160, 0, 160, 255);
                }
                else { SDL_SetRenderDrawColor(renderer, 150, 0, 150, 255); }


                SDL_RenderFillRect(renderer, &ressources->tile);


            }
            else if (oBoard->grid[i * oBoard->iGridLength + j].isVisible == 1) {


                if ((i * oBoard->iGridLength + j) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
                }
                else {
                    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
                }


                if (oBoard->grid[i * oBoard->iGridLength + j].iContent == 0) {
                    SDL_GetRenderDrawColor(renderer, &ressources->fontColor.r, &ressources->fontColor.g, &ressources->fontColor.b, &ressources->fontColor.a);
                }
                else if (oBoard->grid[i * oBoard->iGridLength + j].iContent == 1) {
                    ressources->fontColor = { 66,147, 245, 255 };
                }
                else if (oBoard->grid[i * oBoard->iGridLength + j].iContent == 2) {
                    ressources->fontColor = { 144, 66, 245, 255 };
                }
                else if (oBoard->grid[i * oBoard->iGridLength + j].iContent >= 3) {
                    ressources->fontColor = { 201, 8, 8, 255 };
                }

                sprintf_s(ressources->content, "%d", oBoard->grid[i * oBoard->iGridLength + j].iContent);
                SDL_RenderFillRect(renderer, &ressources->tile);

                ressources->message = TTF_RenderText_Blended(ressources->font, ressources->content, ressources->fontColor);
                ressources->indicTile = SDL_CreateTextureFromSurface(renderer, ressources->message);
                SDL_RenderCopy(renderer, ressources->indicTile, NULL, &ressources->tile);
            }
        }
    }

    SDL_RenderPresent(renderer);


}


void eventHandler(SDL_Event* event, Board* oBoard) {

    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:

        int x = floor(event->button.x / 50);
        int y = floor(event->button.y / 50);
        if (event->button.button == 1 && isCoordInGrid(&oBoard->iGridLength, x, y)) {
            revealCase(oBoard, x, y);
        }
        else if (event->button.button == 3 && isCoordInGrid(&oBoard->iGridLength, x, y)) {
            setFlag(oBoard, x, y);
        }
        break;
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



//initMenu -> initButton
//            placeButton
//            x,y to button
//
//while handleEvents ->
//if button->isClicked(Button) {
//    button->callback()
//    }
//
//isClickedRectBox
//
//isClickedRoundBoxx, y, width, height, callback, display, int isClicked(x, y)


