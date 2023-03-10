#ifndef SCREEN_MSGAME_H_INCLUDED
#define SCREEN_MSGAME_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_mixer.h>

#include "..\components\menu.h"
#include "..\games\mslogic.h"

typedef struct MSSDL_Ressources {
    SDL_Rect tile;
    SDL_Color fontColor;
    TTF_Font* font;
    SDL_Surface* message;
    char content[2];
    SDL_Texture* indicTile;
    SDL_Surface* flagImg;
    SDL_Texture* flagTexture;
    SDL_Surface* mineImg;
    SDL_Texture* mineTexture;
} MSSDL_Ressources;

typedef struct ScreenMS {
    Board oBoard;
    Menu UIMenu;
    MSSDL_Ressources SDLRessources;
    Mix_Music* loop;
} ScreenMS;

void constructScreenMS(ScreenMS* pScreenMS, int difficulty, SDL_Renderer* renderer);
void loadMSSDLRessources(MSSDL_Ressources* SDLRessources, SDL_Renderer* renderer);
void displayMSGame(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer);
void MSGameEventsHandler(MainScreen* oMainScreen, SDL_Event* event);
void destroyScreenMS(void* pScreenMS);

#endif