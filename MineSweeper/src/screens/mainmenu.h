#ifndef SCREEN_MAINMENU_H_INCLUDED
#define SCREEN_MAINMENU_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "..\utils\global.h"
#include "..\components\menu.h"

/**
* Constructs the main menu and initializes the buttons list.
* @param Menu* menu - destination pointer.
* @SDL_Renderer* renderer - The struct containing the rendering state.
*/
void constructScreenMainMenu(Menu* menu, SDL_Renderer* renderer);

/**
* Constructs the difficulty selection menu and initializes the buttons list.
* @param Menu* menu - destination pointer.
* @SDL_Renderer* renderer - The struct containing the rendering state.
*/
void constructScreenDiffSelectMenu(Menu* menu, SDL_Renderer* renderer);

#endif