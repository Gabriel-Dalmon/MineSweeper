#include "menu.h"



void constructMenu(Menu* menu) {
    int relativY = GetSystemMetrics(SM_CYSCREEN) / 4;
    for (int i = 0; i < menu->nbButtons; i++) {
        menu->buttons[i].positionX = GetSystemMetrics(SM_CXSCREEN) / 2 - menu->buttons[i].width;
        menu->buttons[i].positionY = relativY;
        relativY += menu->buttons[i].height + 150;
    }
}

void loadMenuSDLRessources(MenuSDL_Ressources* SDLRessources, SDL_Renderer* renderer) {
    SDLRessources->tile.w = SDLRessources->tile.h = 50;
    SDLRessources->font = TTF_OpenFont("fonts/ttf-bitstream-vera-1.10/Vera.ttf", 96);
}

void destroyMenu(void* pMenu) {
    TTF_CloseFont(((Menu*)pMenu)->SDLRessources.font);
    free(((Menu*)pMenu)->buttons);
}

void displayMenu(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer) {
    Menu* activeMenu = (Menu*)activeScreen;
    for (int i = 0; i < activeMenu->nbButtons; i++) {
        activeMenu->buttons[i].shape(&activeMenu->buttons[i], &activeMenu->SDLRessources, renderer);
    }
}


void menuEventsHandler(MainScreen* mainScreen, SDL_Event* event) {
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:

        Menu* menu = (Menu*)mainScreen->activeScreen;

        int x = floor(event->button.x);
        int y = floor(event->button.y);

        if (event->button.button == 1) {
            for (int i = 0; i < menu->nbButtons; i++) {
                if (menu->buttons[i].isClicked(x, y, &menu->buttons[i]) == 1) {
                    void(*action)(MainScreen * oMainScreen) = menu->buttons[i].action;
                    action(mainScreen);
                    if (menu->buttons[i].type == 1) {
                        destroyMenu(menu);
                        break;
                    }
                }
            }
        }
        break;
    }
}

void printRectBtn(Button* button, MenuSDL_Ressources* SDLRessources, SDL_Renderer* renderer) {

    SDLRessources->tile = { button->positionX, button->positionY , button->width, button->height };
    SDL_SetRenderDrawColor(renderer, 40, 6, 66, 255);
    SDL_RenderFillRect(renderer, &SDLRessources->tile);
    SDLRessources->message = TTF_RenderText_Blended(SDLRessources->font, button->text, { 255, 255, 255, 255 });
    SDLRessources->indicTile = SDL_CreateTextureFromSurface(renderer, SDLRessources->message);
    SDL_RenderCopy(renderer, SDLRessources->indicTile, NULL, &SDLRessources->tile);

    SDL_FreeSurface(SDLRessources->message);
    SDL_DestroyTexture(SDLRessources->indicTile);
}



int rectIsClicked(int x, int y, Button* button) {
    if (button->positionX < x && x < button->positionX + button->width && button->positionY < y && y < button->positionY + button->height) {
        return 1;
    }
    else {
        return 0;
    }
}

