#include "switches.h"
#include "..\utils\global.h"
#include "..\screens\mainmenu.h"
#include "..\screens\msgame.h"
#include "..\components\popup.h"

void switchToMSGame(MainScreen* oMainScreen) {
    oMainScreen->activeScreen = realloc(oMainScreen->activeScreen, sizeof(ScreenMS));
    constructScreenMS((ScreenMS*)oMainScreen->activeScreen, oMainScreen->renderer);
    oMainScreen->displayScreen = displayMSGame;
    oMainScreen->eventsHandler = MSGameEventsHandler;
}



void switchToMainMenu(MainScreen* oMainScreen) {
    oMainScreen->activeScreen = realloc(oMainScreen->activeScreen, sizeof(Menu));
    constructScreenMainMenu((Menu*)oMainScreen->activeScreen, oMainScreen->renderer);
    oMainScreen->displayScreen = displayMenu;
    oMainScreen->eventsHandler = mainMenuEventsHandler;
}



void switchToEndPopup(MainScreen* oMainScreen) {
    Popup* pPopup = (Popup*)malloc(sizeof(Popup));
    constructEndPopup(pPopup, oMainScreen->activeScreen, oMainScreen->displayScreen, oMainScreen->renderer);
    oMainScreen->activeScreen = pPopup;

    oMainScreen->displayScreen = displayPopup;
    oMainScreen->eventsHandler = mainMenuEventsHandler;
}