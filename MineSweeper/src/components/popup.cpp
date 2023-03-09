#include "..\utils\switches.h"
#include "popup.h"




void displayPopup(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer) {
    Popup* activePopup = (Popup*)activeScreen;
    activePopup->displayBack(activePopup->displayBackContent, window, renderer);//crash ici

    for (int i = 0; i < activePopup->activePlace->nbButtons; i++) {
        activePopup->activePlace->buttons[i].shape(&activePopup->activePlace->buttons[i], renderer);
        SDL_RenderPresent(renderer);
    }
}


void constructEndPopup(Popup* popup, SDL_Renderer* renderer) {
    
    popup->activePlace = (Menu*)malloc(sizeof(Menu*));

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