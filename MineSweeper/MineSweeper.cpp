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

