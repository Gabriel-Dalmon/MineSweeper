#include "..\utils\switches.h"
#include "popup.h"


void constructEndPopup(Popup* popup, void* backgroundScreen, void (*displayBackgroundScreen)(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer), void (*destroyBackgroundScreen)(void* activeScreen), SDL_Renderer* renderer) {
    
    popup->backgroundScreen = backgroundScreen;
    popup->displayBackgroundScreen = displayBackgroundScreen;
    popup->destroyBackgroundScreen = destroyBackgroundScreen;
    //assigniation de la liste des boutons
    popup->oMenuButtonsList.nbButtons = 2;
    popup->oMenuButtonsList.buttons = (Button*)malloc(sizeof(Button) * popup->oMenuButtonsList.nbButtons);

    popup->oMenuButtonsList.buttons[0] = { 562,120,NULL,NULL,1,"Play Again",rectIsClicked,switchToDiffSelectMenu,printRectBtn };
    popup->oMenuButtonsList.buttons[1] = { 625,120,NULL,NULL,1,"Back to Menu",rectIsClicked,switchToMainMenu,printRectBtn };

    constructMenu(&popup->oMenuButtonsList);
    loadMenuSDLRessources(&popup->oMenuButtonsList.SDLRessources, renderer);
}


void displayPopup(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer) {
    Popup* activePopup = (Popup*)activeScreen;
    activePopup->displayBackgroundScreen(activePopup->backgroundScreen, window, renderer);
    displayMenu(&activePopup->oMenuButtonsList, window, renderer);
}

void popupEventsHandler(MainScreen* screen, SDL_Event* event) {
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:

        Menu menu = (Menu) ( (Popup*) screen->activeScreen) ->oMenuButtonsList;

        int x = floor(event->button.x);
        int y = floor(event->button.y);

        if (event->button.button == 1) {
            for (int i = 0; i < menu.nbButtons; i++) {
                if (menu.buttons[i].isClicked(x, y, &menu.buttons[i]) == 1) {
                    void(*action)(MainScreen * oMainScreen) = menu.buttons[i].action;
                    void* backgroundScreen = ((Popup*)screen->activeScreen)->backgroundScreen;
                    if (menu.buttons[i].type == 1) {
                        ((Popup*)screen->activeScreen)->destroyBackgroundScreen(backgroundScreen);
                        destroyMenu(&menu);
                        free(backgroundScreen);
                    }
                    action(screen);
                    break;
                }
            }
        }
        break;
    }
}