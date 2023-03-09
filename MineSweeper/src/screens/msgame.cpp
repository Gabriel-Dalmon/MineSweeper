#include "msgame.h"
#include "..\utils\switches.h"

void constructScreenMS(ScreenMS* pScreenMS, SDL_Renderer* renderer) {
    int iGridLength = 15;
    int iDifficulty = 1;
    int iMinesAmount = round(iGridLength * iGridLength / (6 / iDifficulty) / 2);
    constructMSBoard(&pScreenMS->oBoard, iGridLength, iMinesAmount);

    loadMSSDLRessources(&pScreenMS->SDLRessources, renderer);
}
void loadMSSDLRessources(MSSDL_Ressources* SDLRessources, SDL_Renderer* renderer) {
    SDLRessources->tile.w = SDLRessources->tile.h = 50;
    SDLRessources->font = TTF_OpenFont("fonts/ttf-bitstream-vera-1.10/Vera.ttf", 96);
    SDLRessources->flagImg = IMG_Load("img/good_flag.png");
    SDLRessources->flagTexture = SDL_CreateTextureFromSurface(renderer, SDLRessources->flagImg);
}


/**
* @param void* activeScreen, contains SDLRessources & Board
*
*/
void displayMSGame(void* activeScreen, SDL_Window* window, SDL_Renderer* renderer) {

    Board* pBoard = &((ScreenMS*)activeScreen)->oBoard;
    MSSDL_Ressources* pRessources = &((ScreenMS*)activeScreen)->SDLRessources;
    int* iGridLength = &pBoard->iGridLength;

    int winWidth, winHeight;
    SDL_GetWindowSize(window, &winWidth, &winHeight);


    SDL_RenderClear(renderer);

    for (int iRow = 0; iRow < *iGridLength; iRow++) {
        for (int iCol = 0; iCol < *iGridLength; iCol++)
        {
            pRessources->tile.x = iCol * 50 + winWidth / 2 - (50 * *iGridLength) / 2;//{position x * la taille d'une case, position y * la taille d'une case, taille de la case (20 * 20)}
            pRessources->tile.y = iRow * 50 + winHeight / 2 - (50 * *iGridLength) / 2;//{position x * la taille d'une case, position y * la taille d'une case, taille de la case (20 * 20)}

            if (pBoard->grid[iRow * *iGridLength + iCol].isFlag == 1) {

                if ((iRow * pBoard->iGridLength + iCol) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 160, 0, 160, 255);
                }
                else { SDL_SetRenderDrawColor(renderer, 150, 0, 150, 255); }

                SDL_RenderFillRect(renderer, &pRessources->tile);
                SDL_RenderCopy(renderer, pRessources->flagTexture, NULL, &pRessources->tile);


            }
            else if (pBoard->grid[iRow * *iGridLength + iCol].isVisible == 0) {


                if ((iRow * *iGridLength + iCol) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 160, 0, 160, 255);
                }
                else { SDL_SetRenderDrawColor(renderer, 150, 0, 150, 255); }


                SDL_RenderFillRect(renderer, &pRessources->tile);


            }
            else if (pBoard->grid[iRow * pBoard->iGridLength + iCol].isVisible == 1) {


                if ((iRow * *iGridLength + iCol) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
                }
                else {
                    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
                }


                if (pBoard->grid[iRow * pBoard->iGridLength + iCol].iContent == 0) {
                    SDL_GetRenderDrawColor(renderer, &pRessources->fontColor.r, &pRessources->fontColor.g, &pRessources->fontColor.b, &pRessources->fontColor.a);
                }
                else if (pBoard->grid[iRow * pBoard->iGridLength + iCol].iContent == 1) {
                    pRessources->fontColor = { 66,147, 245, 255 };
                }
                else if (pBoard->grid[iRow * pBoard->iGridLength + iCol].iContent == 2) {
                    pRessources->fontColor = { 144, 66, 245, 255 };
                }
                else if (pBoard->grid[iRow * pBoard->iGridLength + iCol].iContent >= 3) {
                    pRessources->fontColor = { 201, 8, 8, 255 };
                }

                sprintf_s(pRessources->content, "%d", pBoard->grid[iRow * pBoard->iGridLength + iCol].iContent);
                SDL_RenderFillRect(renderer, &pRessources->tile);

                pRessources->message = TTF_RenderText_Blended(pRessources->font, pRessources->content, pRessources->fontColor);
                pRessources->indicTile = SDL_CreateTextureFromSurface(renderer, pRessources->message);
                SDL_RenderCopy(renderer, pRessources->indicTile, NULL, &pRessources->tile);

                SDL_FreeSurface(pRessources->message);
                SDL_DestroyTexture(pRessources->indicTile);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void MSGameEventsHandler(MainScreen* oMainScreen, SDL_Event* event) {
    Board* pBoard = &((ScreenMS*)oMainScreen->activeScreen)->oBoard;
    int* iGridLength = &pBoard->iGridLength;
    int winWidth, winHeight;
    SDL_GetWindowSize(oMainScreen->window, &winWidth, &winHeight);

    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:

        int x = floor(event->button.x / 50);
        int y = floor(event->button.y / 50);
        int xCanva = floor((event->button.x - winWidth / 2 + (50 * pBoard->iGridLength) / 2) / 50);
        int yCanva = floor((event->button.y - winHeight / 2 + (50 * pBoard->iGridLength) / 2) / 50);
        if (event->button.button == 1 && isCoordInGrid(&pBoard->iGridLength, xCanva, yCanva)) {
            revealCase(pBoard, xCanva, yCanva);
            pBoard->iCursorPosition[0] = xCanva;
            pBoard->iCursorPosition[1] = yCanva;
        }
        else if (event->button.button == 3 && isCoordInGrid(&pBoard->iGridLength, xCanva, yCanva)) {
            setFlag(pBoard, xCanva, yCanva);
        }
        break;
    }
}