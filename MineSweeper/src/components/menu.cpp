#include <stdio.h>
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
    SDLRessources->flagImg = IMG_Load("img/good_flag.png");
    SDLRessources->flagTexture = SDL_CreateTextureFromSurface(renderer, SDLRessources->flagImg);
}

void displayMenu(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer) {
    Menu* activeMenu = (Menu*)activeScreen;
    for (int i = 0; i < activeMenu->nbButtons; i++) {
        activeMenu->buttons[i].shape(&activeMenu->buttons[i], renderer);
    }
}

void printRectBtn(Button* button, SDL_Renderer* renderer) {
    SDL_Rect rect;
    TTF_Font* vera = TTF_OpenFont("fonts/ttf-bitstream-vera-1.10/Vera.ttf", 128);
    SDL_Surface* message;
    SDL_Texture* indicTile;

    rect = { button->positionX, button->positionY , button->width, button->height };
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderFillRect(renderer, &rect);
    message = TTF_RenderText_Blended(vera, button->text, { 201, 8, 8, 255 });
    indicTile = SDL_CreateTextureFromSurface(renderer, message);
    SDL_RenderCopy(renderer, indicTile, NULL, &rect);
    SDL_FreeSurface(message);
    SDL_DestroyTexture(indicTile);
}



int rectIsClicked(int x, int y, Button* button) {
    if (button->positionX < x && x < button->positionX + button->width && button->positionY < y && y < button->positionY + button->height) {
        return 1;
    }
    else {
        return 0;
    }
}

