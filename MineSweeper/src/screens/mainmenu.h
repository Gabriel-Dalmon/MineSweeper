#ifndef SCREEN_MAINMENU_H_INCLUDED
#define SCREEN_MAINMENU_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "..\utils\global.h"
#include "..\components\menu.h"


void constructScreenMainMenu(Menu* menu, SDL_Renderer* renderer);
void constructScreenDiffSelectMenu(Menu* menu, SDL_Renderer* renderer);

#endif