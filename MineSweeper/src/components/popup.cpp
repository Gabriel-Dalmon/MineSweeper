#include "..\utils\switches.h"
#include "popup.h"






void constructEndPopup(Popup* popup, void* backgroundScreen, void (*displayBackgroundScreen)(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer), SDL_Renderer* renderer) {
    
    popup->backgroundScreen = backgroundScreen;
    popup->displayBackgroundScreen = displayBackgroundScreen;
    //assigniation de la liste des boutons
    popup->oMenuButtonsList.nbButtons = 2;
    popup->oMenuButtonsList.buttons = (Button*)malloc(sizeof(Button) * popup->oMenuButtonsList.nbButtons);


    popup->oMenuButtonsList.buttons[0].width = 250;
    popup->oMenuButtonsList.buttons[0].height = 75;
    popup->oMenuButtonsList.buttons[0].text = "play again";
    popup->oMenuButtonsList.buttons[0].shape = printRectBtn;
    popup->oMenuButtonsList.buttons[0].isClicked = rectIsClicked;
    popup->oMenuButtonsList.buttons[0].action = switchToMSGame;

    popup->oMenuButtonsList.buttons[1].width = 250;
    popup->oMenuButtonsList.buttons[1].height = 75;
    popup->oMenuButtonsList.buttons[1].text = "back to menu";
    popup->oMenuButtonsList.buttons[1].shape = printRectBtn;
    popup->oMenuButtonsList.buttons[1].isClicked = rectIsClicked;
    popup->oMenuButtonsList.buttons[1].action = switchToMainMenu;

    constructMenu(&popup->oMenuButtonsList);
    loadMenuSDLRessources(&popup->oMenuButtonsList.SDLRessources, renderer);
}


void displayPopup(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer) {
    Popup* activePopup = (Popup*)activeScreen;
    activePopup->displayBackgroundScreen(activePopup->backgroundScreen, window, renderer);//crash ici

    for (int i = 0; i < activePopup->oMenuButtonsList.nbButtons; i++) {
        activePopup->oMenuButtonsList.buttons[i].shape(&activePopup->oMenuButtonsList.buttons[i], renderer);
        SDL_RenderPresent(renderer);
    }
}