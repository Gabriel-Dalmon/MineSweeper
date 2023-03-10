
#include "mainmenu.h"
#include "..\components\menu.h"
#include "..\utils\switches.h"


void constructScreenMainMenu(Menu* menu, SDL_Renderer* renderer) {

    //assigniation de la liste des boutons
    menu->nbButtons = 2;
    menu->buttons = (Button*)malloc(sizeof(Button) * menu->nbButtons);
    menu->buttons[0].width = 250;
    menu->buttons[0].height = 120;
    menu->buttons[0].type = 1;
    menu->buttons[0].text = "Play";
    menu->buttons[0].shape = printRectBtn;
    menu->buttons[0].isClicked = rectIsClicked;
    menu->buttons[0].action = switchToDiffSelectMenu;

    menu->buttons[1] = { 250,120,NULL,NULL,0,"Quit", rectIsClicked, quitApp, printRectBtn };


    constructMenu(menu);
    loadMenuSDLRessources(&menu->SDLRessources, renderer);
}

void constructScreenDiffSelectMenu(Menu* menu, SDL_Renderer* renderer) {

    //assigniation de la liste des boutons
    menu->nbButtons = 3;
    menu->buttons = (Button*)malloc(sizeof(Button) * menu->nbButtons);

    menu->buttons[0].width = 125;
    menu->buttons[0].height = 60;
    menu->buttons[0].text = "Easy";
    menu->buttons[0].shape = printRectBtn;
    menu->buttons[0].isClicked = rectIsClicked;
    menu->buttons[0].action = switchToMSGameEasy;

    menu->buttons[1].width = 187;
    menu->buttons[1].height = 60;
    menu->buttons[1].text = "Normal";
    menu->buttons[1].shape = printRectBtn;
    menu->buttons[1].isClicked = rectIsClicked;
    menu->buttons[1].action = switchToMSGameNormal;

    menu->buttons[2].width = 125;
    menu->buttons[2].height = 60;
    menu->buttons[2].text = "Hard";
    menu->buttons[2].shape = printRectBtn;
    menu->buttons[2].isClicked = rectIsClicked;
    menu->buttons[2].action = switchToMSGameHard;



    constructMenu(menu);
    loadMenuSDLRessources(&menu->SDLRessources, renderer);
}