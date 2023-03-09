#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


typedef struct MainScreen {
    void* activeScreen;
    SDL_Window* window;
    SDL_Renderer* renderer;
    void (*displayScreen)(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer);
    void (*eventsHandler)(MainScreen* oMainScreen, SDL_Event* events);
} MainScreen;

void constructMainScreen(MainScreen* oMainScreen);


#endif


