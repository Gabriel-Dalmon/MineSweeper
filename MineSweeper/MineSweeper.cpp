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

#include "headers\mslogic.h"
#include "headers\msutils.h"

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
    Board oBoard;
    Menu UIMenu;
    MSSDL_Ressources SDLRessources;
} ScreenMS;

void constructScreenMS(ScreenMS* pScreenMS, SDL_Renderer* renderer);
void loadMSSDLRessources(MSSDL_Ressources* SDLRessources, SDL_Renderer* renderer);
void switchToMSGame(MainScreen* oMainScreen);
void displayMSGame(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer);
void MSGameEventsHandler(MainScreen* oMainScreen, SDL_Event* event);


typedef struct MenuSDL_Ressources {
    SDL_Rect tile;
    SDL_Color fontColor;
    TTF_Font* font;
    SDL_Surface* message;
    char content[2];
    SDL_Texture* indicTile;
    SDL_Surface* flagImg;
    SDL_Texture* flagTexture;
} MenuSDL_Ressources;

typedef struct Button {
    int height;
    int width;
    int positionX;
    int positionY;
    const char* text;
    int(*isClicked)(int x, int y, Button* button);
    void(*action)(MainScreen* oMainScreen);
    void(*shape)(Button* button, SDL_Renderer* renderer);
}Button;

typedef struct Menu {
    char* title;
    MenuSDL_Ressources SDLRessources;
    Button* buttons; //on a une liste de boutons avec leurs caracteristiques et MenuMado va devoir les afficher
    int nbButtons;
} Menu;

typedef struct ScreenMSDiffSelectMenu {
    Menu oMenu;
    MenuSDL_Ressources SDLRessources;
} ScreenMS;

void constructScreenMSDiffSelectMenu(ScreenMSDiffSelectMenu* pScreenMS, SDL_Renderer* renderer);
void loadMenuSDLRessources(MSSDL_Ressources* SDLRessources, SDL_Renderer* renderer);
void switchToMSDiffSelectMenu(MainScreen* oMainScreen);



typedef struct MainScreen {
    void* activeScreen;
    SDL_Window* window;
    SDL_Renderer* renderer;
    void (*displayScreen)(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer);
    void (*eventsHandler)(MainScreen* oMainScreen, SDL_Event* events);
} MainScreen;

void constructMainScreen(MainScreen* oMainScreen);

void mainMenuEventsHandler(MainScreen* mainMenu, SDL_Event* event);
void constructMenu(Menu* menu);


int main(int argc, char* argv[])
{
    TTF_Init();

    //Button play;
    //play.width = 250;
    //play.height = 75;
    //play.text = "DIV";
    //play.shape = printRectBtn;
    //play.isClicked = rectIsClicked;
    //play.action = switchToMSGame;

    MainScreen oMainScreen;
    constructMainScreen(&oMainScreen);
    switchToMSGame(&oMainScreen);

    SDL_Event event;
    while (1) {
        //EVENTS
        while (SDL_PollEvent(&event)) {
            oMainScreen.eventsHandler(&oMainScreen, &event);
        }
        //DISPLAY
        oMainScreen.displayScreen(oMainScreen.activeScreen, oMainScreen.window, oMainScreen.renderer);
    }
    return 0;
}


void constructScreenMS(ScreenMS* pScreenMS, SDL_Renderer* renderer) {    
    int iGridLength = 15; 
    int iDifficulty = 1;
    int iMinesAmount = round(iGridLength * iGridLength / (6 / iDifficulty) / 2);
    constructMSBoard(&pScreenMS->oBoard, iGridLength, iMinesAmount);

    loadMSSDLRessources(&pScreenMS->SDLRessources, renderer);
}
void loadMSSDLRessources(MSSDL_Ressources* SDLRessources, SDL_Renderer* renderer) {
    SDLRessources->tile.w = SDLRessources->tile.h = 50;
    SDLRessources->font = TTF_OpenFont("fonts/ttf-bitstream-vera-1.10/Vera.ttf", 96);
    SDLRessources->flagImg = IMG_Load("img/good_flag.png");
    SDLRessources->flagTexture = SDL_CreateTextureFromSurface(renderer, SDLRessources->flagImg);
}
void switchToMSGame(MainScreen* oMainScreen) {
    oMainScreen->activeScreen = realloc(oMainScreen->activeScreen, sizeof(ScreenMS));
    constructScreenMS((ScreenMS*)oMainScreen->activeScreen, oMainScreen->renderer);
    oMainScreen->displayScreen = displayMSGame;
    oMainScreen->eventsHandler = MSGameEventsHandler;
}
/**
* @param void* activeScreen, contains SDLRessources & Board
* 
*/
void displayMSGame(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer) {

    Board* pBoard = &((ScreenMS*)activeScreen)->oBoard;
    MSSDL_Ressources* pRessources = &((ScreenMS*)activeScreen)->SDLRessources;
    int* iGridLength = &pBoard->iGridLength;

    int winWidth, winHeight;
    SDL_GetWindowSize(window, &winWidth, &winHeight);


    SDL_RenderClear(renderer);

    for (int iRow = 0; iRow < *iGridLength; iRow++) {
        for (int iCol = 0; iCol < *iGridLength; iCol++)
        {
            pRessources->tile.x = iCol * 50 + winWidth/2 - (50 * *iGridLength)/2;//{position x * la taille d'une case, position y * la taille d'une case, taille de la case (20 * 20)}
            pRessources->tile.y = iRow * 50 + winHeight / 2 - (50 * *iGridLength) / 2;//{position x * la taille d'une case, position y * la taille d'une case, taille de la case (20 * 20)}
            
            if (pBoard->grid[iRow * *iGridLength + iCol].isFlag == 1) {

                if ((iRow * pBoard->iGridLength + iCol) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 160, 0, 160, 255);
                }
                else { SDL_SetRenderDrawColor(renderer, 150, 0, 150, 255); }

                SDL_RenderFillRect(renderer, &pRessources->tile);
                SDL_RenderCopy(renderer, pRessources->flagTexture, NULL, &pRessources->tile);


            }
            else if (pBoard->grid[iRow * *iGridLength + iCol].isVisible == 0) {


                if ((iRow * *iGridLength + iCol) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 160, 0, 160, 255);
                }
                else { SDL_SetRenderDrawColor(renderer, 150, 0, 150, 255); }


                SDL_RenderFillRect(renderer, &pRessources->tile);


            }
            else if (pBoard->grid[iRow * pBoard->iGridLength + iCol].isVisible == 1) {


                if ((iRow * *iGridLength + iCol) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
                }
                else {
                    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
                }


                if (pBoard->grid[iRow * pBoard->iGridLength + iCol].iContent == 0) {
                    SDL_GetRenderDrawColor(renderer, &pRessources->fontColor.r, &pRessources->fontColor.g, &pRessources->fontColor.b, &pRessources->fontColor.a);
                }
                else if (pBoard->grid[iRow * pBoard->iGridLength + iCol].iContent == 1) {
                    pRessources->fontColor = { 66,147, 245, 255 };
                }
                else if (pBoard->grid[iRow * pBoard->iGridLength + iCol].iContent == 2) {
                    pRessources->fontColor = { 144, 66, 245, 255 };
                }
                else if (pBoard->grid[iRow * pBoard->iGridLength + iCol].iContent >= 3) {
                    pRessources->fontColor = { 201, 8, 8, 255 };
                }

                sprintf_s(pRessources->content, "%d", pBoard->grid[iRow * pBoard->iGridLength + iCol].iContent);
                SDL_RenderFillRect(renderer, &pRessources->tile);

                pRessources->message = TTF_RenderText_Blended(pRessources->font, pRessources->content, pRessources->fontColor);
                pRessources->indicTile = SDL_CreateTextureFromSurface(renderer, pRessources->message);
                SDL_RenderCopy(renderer, pRessources->indicTile, NULL, &pRessources->tile);
           
                SDL_FreeSurface(pRessources->message);
                SDL_DestroyTexture(pRessources->indicTile);
            }
        }
    }

    SDL_RenderPresent(renderer);
}
void MSGameEventsHandler(MainScreen* oMainScreen, SDL_Event* event) {
    Board* pBoard = &((ScreenMS*)oMainScreen->activeScreen)->oBoard;
    int* iGridLength = &pBoard->iGridLength;
    int winWidth, winHeight;
    SDL_GetWindowSize(oMainScreen->window, &winWidth, &winHeight);

    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:

        int x = floor(event->button.x / 50);
        int y = floor(event->button.y / 50);
        int xCanva = floor((event->button.x - winWidth / 2 + (50 * pBoard->iGridLength) / 2) / 50);
        int yCanva = floor((event->button.y - winHeight / 2 + (50 * pBoard->iGridLength) / 2) / 50);
        printf("(%d|%d) - (%d|%d)", x, y, xCanva, yCanva);
        if (event->button.button == 1 && isCoordInGrid(&pBoard->iGridLength, xCanva, yCanva)) {
            revealCase(pBoard, xCanva, yCanva);
            pBoard->iCursorPosition[0] = xCanva;
            pBoard->iCursorPosition[1] = yCanva;
        }
        else if (event->button.button == 3 && isCoordInGrid(&pBoard->iGridLength, xCanva, yCanva)) {
            setFlag(pBoard, xCanva, yCanva);
        }
        break;
    }
}

void constructScreenMSDiffSelectMenu(ScreenMSDiffSelectMenu* pActiveScreen, SDL_Renderer* renderer) {
    constructMenu(&pActiveScreen->oMenu);
    loadMenuSDLRessources(pActiveScreen->oMenu.SDLRessources, renderer);
}

void switchToMSDiffSelectMenu(MainScreen* oMainScreen);

void constructMainScreen(MainScreen* oMainScreen) {
    oMainScreen->window = SDL_CreateWindow("MineSweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SDL_WINDOW_RESIZABLE);
    oMainScreen->renderer = SDL_CreateRenderer(oMainScreen->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    oMainScreen->activeScreen = malloc(sizeof(int));
}

void constructMenu(Menu* menu) {
    int relativY = GetSystemMetrics(SM_CYSCREEN) / 4;
    for (int i = 0; i < menu->nbButtons; i++) {
        menu->buttons[i].positionX = GetSystemMetrics(SM_CXSCREEN) / 2 - menu->buttons[i].width;
        menu->buttons[i].positionY = relativY;
        relativY += menu->buttons[i].height + 150;
    }
}

void loadMenuSDLRessources(MSSDL_Ressources* SDLRessources, SDL_Renderer* renderer);

void printRectBtn(Button* button, SDL_Renderer* renderer) {
    SDL_Rect shape;
    TTF_Font* vera = TTF_OpenFont("fonts/ttf-bitstream-vera-1.10/Vera.ttf", 128);
    SDL_Surface* message;
    SDL_Texture* indicTile;


    shape = { button->positionX, button->positionY , button->width, button->height };
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderFillRect(renderer, &shape);
    message = TTF_RenderText_Blended(vera, button->text, { 201, 8, 8, 255 });
    indicTile = SDL_CreateTextureFromSurface(renderer, message);
    SDL_RenderCopy(renderer, indicTile, NULL, &shape);
}

int rectIsClicked(int x, int y, Button* button) {
    if (button->positionX < x < button->positionX + button->width && button->positionY < y < button->positionY + button->height) {
        return 1;
    }
    else {
        return 0;
    }
}


void displayMenu(MainScreen* menu) {

    ScreenMenu* activeMenu = (ScreenMenu*)menu->activeScreen;
    for (int i = 0; i < activeMenu->nbButtons; i++) {
        activeMenu->buttons[i].shape(&activeMenu->buttons[i], menu->renderer);
    }

    SDL_RenderPresent(menu->renderer);
}

void mainMenuEventsHandler(MainScreen* mainMenu, SDL_Event* event) {
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:

        ScreenMenu* menu = (ScreenMenu*)mainMenu->activeScreen;

        int x = floor(event->button.x);
        int y = floor(event->button.y);

        if (event->button.button == 1) {
            for (int i = 0; i < menu->nbButtons; i++) {
                if (menu->buttons[i].isClicked(x, y, menu->buttons) == 1) {
                    menu->buttons[i].action(mainMenu);
                }
            }
        }
        break;
    }
}



//void switchToMainMenu(MainScreen* oMainScreen) {
//    oMainScreen->activeScreen = constructScreenMainMenu();
//    oMainScreen->displayScreen = displayMainMenu;
//    oMainScreen->eventsHandler = mainMenuEventsHandler;
//}

//ScreenMenu* constructScreenMainMenu() {
//    ScreenMenu oScreenMenu;
//    //assigniation de la liste des boutons
//    initMenu(&oScreenMenu);
//    return &oScreenMenu;
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


/*
* 
* button -> action(void* this, void* this)
* 
* GameMado game mado -> display Game
* MenuMado menu mado -> display Menu
Main : Mado mainMado -> display, eventHandler...

switchMadoToGame(void* this) :
    Mado* mado = (Mado*) this;

quitGame(void* this)
    int* arg = (int)

update main mado display, eventhandler with game display, game eventhandler = displayMado = displayGame

switchMadoToMenu : update main mado display, eventhandler with menu display, menu eventhandler



*/