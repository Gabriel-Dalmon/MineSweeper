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


typedef struct Popup {
    void(*displayBack)(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer);
    void* displayBackContent;
    Menu* activePlace;
} Popup;





void constructScreenMSDiffSelectMenu(ScreenMSDiffSelectMenu* pScreenMS, SDL_Renderer* renderer);

//void switchToMSDiffSelectMenu(MainScreen* oMainScreen);


void constructEndPopup(Popup* popup, SDL_Renderer* renderer);
void switchToEndPopup(MainScreen* oMainScreen);
void displayPopup(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer);

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







void switchToEndPopup(MainScreen* oMainScreen) {
    Popup popup;
    popup.displayBack = oMainScreen->displayScreen;
    popup.displayBackContent = (oMainScreen->activeScreen);
    popup.displayBackContent = oMainScreen->activeScreen;

    realloc(oMainScreen->activeScreen, sizeof(Popup));

    constructEndPopup((Popup*)oMainScreen->activeScreen, oMainScreen->renderer);

    oMainScreen->displayScreen = displayPopup;
    oMainScreen->eventsHandler = mainMenuEventsHandler;
}





void displayPopup(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer) {
    Popup* activePopup = (Popup*)activeScreen;
    activePopup->displayBack(activePopup->displayBackContent, window, renderer);
    for (int i = 0; i < activePopup->activePlace->nbButtons; i++) {
        activePopup->activePlace->buttons[i].shape(&activePopup->activePlace->buttons[i], renderer);


        SDL_RenderPresent(renderer);
    }
}


void constructEndPopup(Popup* popup, SDL_Renderer* renderer) {

    //assigniation de la liste des boutons
    popup->activePlace->nbButtons = 2;
    popup->activePlace->buttons = (Button*)malloc(sizeof(Button) * popup->activePlace->nbButtons);
               
    popup->activePlace->buttons[0].width = 250;
    popup->activePlace->buttons[0].height = 75;
    popup->activePlace->buttons[0].text = "play again";
    popup->activePlace->buttons[0].shape = printRectBtn;
    popup->activePlace->buttons[0].isClicked = rectIsClicked;
    popup->activePlace->buttons[0].action = switchToMSGame;
                      
    popup->activePlace->buttons[1].width = 250;
    popup->activePlace->buttons[1].height = 75;
    popup->activePlace->buttons[1].text = "back to menu";
    popup->activePlace->buttons[1].shape = printRectBtn;
    popup->activePlace->buttons[1].isClicked = rectIsClicked;
    popup->activePlace->buttons[1].action = switchToMainMenu;

    constructMenu(popup->activePlace);
    loadMenuSDLRessources(&popup->activePlace->SDLRessources, renderer);
}

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