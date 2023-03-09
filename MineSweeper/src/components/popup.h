#ifndef COMPONENTS_POPUP_H_INCLUDED
#define COMPONENTS_POPUP_H_INCLUDED


#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>

#include "..\utils\global.h"
#include "..\components\menu.h"


typedef struct Popup {
    void(*displayBack)(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer);
    void* displayBackContent;
    Menu* activePlace;
} Popup;

void constructEndPopup(Popup* popup, SDL_Renderer* renderer);
void displayPopup(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer);

#endif