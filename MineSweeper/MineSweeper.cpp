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
#include <SDL_mixer.h>

#include "src\games\mslogic.h"
#include "src\components\menu.h"
#include "src\screens\msgame.h"
#include "src\screens\mainmenu.h"
#include "src\utils\global.h"
#include "headers\msutils.h"
#include "src\utils\switches.h"





typedef struct ScreenMSDiffSelectMenu {
    Menu oMenu;
} ScreenMSDiffSelectMenu;








void constructScreenMSDiffSelectMenu(ScreenMSDiffSelectMenu* pScreenMS, SDL_Renderer* renderer);

//void switchToMSDiffSelectMenu(MainScreen* oMainScreen);




int main(int argc, char* argv[])
{
    TTF_Init();
    Mix_Init(0x00000008);//on iinitialise au format mp3
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    

    MainScreen oMainScreen;
    constructMainScreen(&oMainScreen);
    switchToMainMenu(&oMainScreen);

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



void constructScreenMSDiffSelectMenu(ScreenMSDiffSelectMenu* pActiveScreen, SDL_Renderer* renderer) {
    constructMenu(&pActiveScreen->oMenu);
    loadMenuSDLRessources(&pActiveScreen->oMenu.SDLRessources, renderer);
}

//void switchToMSDiffSelectMenu(MainScreen* oMainScreen);















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

// struct Button, struct Menu, constructMainMenu, constructDiffSelectMenu..., displayMenu, MenuEventHandler

/**
* Popup
*   void(*displayBackground)(void* previousScreen, renderer);
*   void* previousScreen;
*   
* 
* ***
* SwitchToPopup
*   previousScreen = activeScreen;
*   displayBackground = displayMainMenu;
*   
*   //updateMainScreen
*   display = displayPopup
* 
*
* ***
* MainScreen
*   display : displayGame -> displayPopup
*
* ***
* displayPopup(){
* displayBackground
* code to display the Popup
}
* 
*/
// Popup : pfn displayBackground