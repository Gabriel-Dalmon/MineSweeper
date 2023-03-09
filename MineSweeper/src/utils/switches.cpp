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
    Popup popup;
    //popup.displayBack = malloc(sizeof(void*));
    popup.displayBack = oMainScreen->displayScreen;
    popup.displayBackContent = malloc(sizeof(void*));
    popup.displayBackContent = oMainScreen->activeScreen;

    oMainScreen->activeScreen = malloc(sizeof(Popup*));

    constructEndPopup((Popup*)oMainScreen->activeScreen, oMainScreen->renderer);

    oMainScreen->displayScreen = displayPopup;
    oMainScreen->eventsHandler = mainMenuEventsHandler;
}