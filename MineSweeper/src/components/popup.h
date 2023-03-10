#ifndef COMPONENTS_POPUP_H_INCLUDED
#define COMPONENTS_POPUP_H_INCLUDED


#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>

#include "..\utils\global.h"
#include "..\components\menu.h"


typedef struct Popup {
    void(*displayBackgroundScreen)(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer);
    void (*destroyBackgroundScreen)(void* activeScreen);
    void* backgroundScreen;
    Menu oMenuButtonsList;
} Popup;

void constructEndPopup(Popup* popup, void* backgroundScreen, void (*displayBackgroundScreen)(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer), void (*destroyBackgroundScreen)(void* activeScreen), SDL_Renderer* renderer);
void displayPopup(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer);
void popupEventsHandler(MainScreen* mainMenu, SDL_Event* event);

#endif