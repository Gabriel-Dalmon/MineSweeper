
#include "mainmenu.h"
#include "..\components\menu.h"
#include "..\utils\switches.h"


void constructScreenMainMenu(Menu* menu, SDL_Renderer* renderer) {

    //assigniation de la liste des boutons
    menu->nbButtons = 1;
    menu->buttons = (Button*)malloc(sizeof(Button) * menu->nbButtons);
    menu->buttons[0].width = 250;
    menu->buttons[0].height = 75;
    menu->buttons[0].text = "DIV";
    menu->buttons[0].shape = printRectBtn;
    menu->buttons[0].isClicked = rectIsClicked;
    menu->buttons[0].action = switchToMSGame;
    constructMenu(menu);
    loadMenuSDLRessources(&menu->SDLRessources, renderer);

}


void mainMenuEventsHandler(MainScreen* mainMenu, SDL_Event* event) {
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:

        Menu* menu = (Menu*)mainMenu->activeScreen;

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