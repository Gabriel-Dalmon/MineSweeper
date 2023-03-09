#ifndef COMPONENT_MENU_H_INCLUDED
#define COMPONENT_MENU_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <windows.h>

#include "..\utils\global.h"

typedef struct MenuSDL_Ressources {
    SDL_Rect tile;
    SDL_Color fontColor;
    TTF_Font* font;
    SDL_Surface* message;
    char content[2];
    SDL_Texture* indicTile;
    SDL_Surface* flagImg;
    SDL_Texture* flagTexture;
} MenuSDL_Ressources;

typedef struct Button {
    int height;
    int width;
    int positionX;
    int positionY;
    const char* text;
    int(*isClicked)(int x, int y, Button* button);
    void(*action)(MainScreen* oMainScreen);
    void(*shape)(Button* button, SDL_Renderer* renderer);
}Button;

typedef struct Menu {
    char* title;
    MenuSDL_Ressources SDLRessources;
    Button* buttons; //on a une liste de boutons avec leurs caracteristiques et MenuMado va devoir les afficher
    int nbButtons;
} Menu;


/**
* PROTOTYPES
*/

/**
* Gives buttons a position XY
*@param Menu* menu - pointer to the menu object to  
*/
void constructMenu(Menu* menu);

/**
* Loads/inits the SDL ressources that will be applied to buttons
* @param Menu* menu - pointer to the menu object
* @param SDL_Renderer renderer - pointer to the renderer element from SDL library
*/
void loadMenuSDLRessources(MenuSDL_Ressources* SDLRessources, SDL_Renderer* renderer);

void displayMenu(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer);

void printRectBtn(Button* button, SDL_Renderer* renderer);
int rectIsClicked(int x, int y, Button* button);

#endif