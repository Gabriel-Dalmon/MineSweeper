#include "switches.h"
#include "..\utils\global.h"
#include "..\screens\mainmenu.h"
#include "..\screens\msgame.h"
#include "..\components\popup.h"



void switchToMSGameEasy(MainScreen* oMainScreen) {
    switchToMSGame(oMainScreen, 1);
}

void switchToMSGameNormal(MainScreen* oMainScreen) {
    switchToMSGame(oMainScreen, 2);
}

void switchToMSGameHard(MainScreen* oMainScreen) {
    switchToMSGame(oMainScreen, 3);
}

void switchToMSGame(MainScreen* oMainScreen, int difficulty) {
    oMainScreen->activeScreen = realloc(oMainScreen->activeScreen, sizeof(ScreenMS));
    constructScreenMS((ScreenMS*)oMainScreen->activeScreen, difficulty, oMainScreen->renderer);
    oMainScreen->displayScreen = displayMSGame;
    oMainScreen->eventsHandler = MSGameEventsHandler;
    oMainScreen->destroyActiveScreen = destroyScreenMS;
    Mix_PlayMusic(((ScreenMS*)oMainScreen->activeScreen)->loop, -1);
}



void switchToMainMenu(MainScreen* oMainScreen) {
    oMainScreen->activeScreen = realloc(oMainScreen->activeScreen, sizeof(Menu));
    constructScreenMainMenu((Menu*)oMainScreen->activeScreen, oMainScreen->renderer);
    oMainScreen->displayScreen = displayMenu;
    oMainScreen->eventsHandler = menuEventsHandler;
}

void switchToDiffSelectMenu(MainScreen* oMainScreen) {
    oMainScreen->activeScreen = realloc(oMainScreen->activeScreen, sizeof(Menu));
    constructScreenDiffSelectMenu((Menu*)oMainScreen->activeScreen, oMainScreen->renderer);
    oMainScreen->displayScreen = displayMenu;
    oMainScreen->eventsHandler = menuEventsHandler;
}

void switchToEndPopup(MainScreen* oMainScreen) {
    Mix_HaltMusic();

    Popup* pPopup = (Popup*)malloc(sizeof(Popup));
    constructEndPopup(pPopup, oMainScreen->activeScreen, oMainScreen->displayScreen, oMainScreen->destroyActiveScreen, oMainScreen->renderer);
    oMainScreen->activeScreen = pPopup;

    oMainScreen->displayScreen = displayPopup;
    oMainScreen->eventsHandler = popupEventsHandler;
}


#include <stdio.h>
void quitApp(MainScreen* oMainScreen) {
    oMainScreen->isAppRunning = 0;
}
