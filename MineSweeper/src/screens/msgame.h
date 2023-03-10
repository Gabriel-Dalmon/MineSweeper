#ifndef SCREEN_MSGAME_H_INCLUDED
#define SCREEN_MSGAME_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_mixer.h>

#include "..\components\menu.h"
#include "..\games\mslogic.h"

/**
* All the SDL Ressources initializations for the MineSweeper Game Board.
*/
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

/**
* Necessary Data to display the MineSweeper Game Board.
*/
typedef struct ScreenMS {
    Board oBoard;
    Menu UIMenu;
    MSSDL_Ressources SDLRessources;
    Mix_Music* loop;
} ScreenMS;



/**
* @param ScreenMS* pScreenMS - destination pointer to create a new struct ScreenMS.
* @param int difficulty - will define the size of the board and the amount of the mines.
* @param SDL_Renderer* renderer - The struct containing the rendering state.
*/
void constructScreenMS(ScreenMS* pScreenMS, int difficulty, SDL_Renderer* renderer);

/**
* Assigns default values to SDLRessources.
* @param MSSDL_Ressources* SDLRessources - destination pointer to define the SDL ressources.
* @param SDL_Renderer* renderer - The struct containing the rendering state.
*/
void loadMSSDLRessources(MSSDL_Ressources* SDLRessources, SDL_Renderer* renderer);

/**
* @param void* activeScreen - will be cast to ScreenMS* / pointer to the Data used to display the MineSweeper Game Board.
* @param SDL_Window* window - window where the informations will be displayed.
* @param SDL_Renderer* renderer - The struct containing the rendering state.
*/
void displayMSGame(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer);

/**
* Handles click on the game board and call functions in case of trigger.
* @param MainScreen* oMainScreen - destination to edit for switches .
* @param SDL_Event* event - A union that contains structures for the different event types.
*/
void MSGameEventsHandler(MainScreen* oMainScreen, SDL_Event* event);

/**
* Clean all the previously allocated memory in ScreenMS type such as MSSDL_Ressources or the game board.
* @param void* pScreenMS - will be cast into a ScreenMS.
*/
void destroyScreenMS(void* pScreenMS);

#endif