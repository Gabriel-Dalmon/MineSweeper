// Démineur.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <windows.h>


#define MADO_HEAD                           \
            SDL_Window* window ;            \
            SDL_Renderer* renderer;         \
            //void(*display)(void* render);   \
            //void(*control)(void* render);   \

            



typedef struct Case {
    int content;
    int isVisible; // 1 = visible, 0 = hidden;
    int indicator;
    int flag = 0; //1 = drapeau, 0 = pas de drapeau
    int current = 0; // position du joueur : si 1, le joueur est ici

} Case;

typedef struct Board {
    Case* grid;
    int size;
    int remaining;
    int iMinesAmount;
} Board;


typedef struct Button{
    int height;
    int width;
    int positionX;
    int positionY;
    const char* text;
    void* adress;
    int(*isClicked)(int x, int y, Button* button);
    void(*control)(void* something, ...);
    void(*print)(Button* button, SDL_Renderer* renderer);
}Button;






typedef struct GameMado {
    MADO_HEAD
    Board* board; //gros commentaire
    void(*control)(SDL_Event* event, Board* table);
    int active;
} GMado;

typedef struct MenuMado {
    MADO_HEAD
    Button* buttons; //on a une liste de boutons avec leurs caracteristiques et MenuMado va devoir les afficher
    void(*control)(SDL_Event* event, MenuMado* menu, GMado* toChange);
    int nbButtons;
} MMado;



Board init(int size, int mines);
void reveal(Board* table, int x, int y);
void check(Board* table, int x, int y);
void setFlag(Board* table, int x, int y);
void generateMines(Board* oBoard);
void oddToEvenByLower(int* number);
void checkWin(Board* table, int x, int y, int* playing);
void displayUI(GMado* game);
void displayMenu(MMado* menu);
void gameControl(SDL_Event* event, Board* table);
void controlMenu(SDL_Event* event, MMado* menu, GMado* toChange);
void initMenu(MMado* menu);
void printRectBtn(Button* button, SDL_Renderer* renderer);
void goToGameAdress(void* smth, ...);
void goToMenuAdress(GMado* game, MMado* menu, MMado* activeOne);
int rectIsClicked(int x, int y, Button* button);


int main(int argc, char* argv[])
{



    int size;
    printf("Entrez une taille de grille : ");
    int res = scanf_s("%d", &size);

    int iMinesAmount;
    printf("Enter the amount of mines present on the grid : ");
    scanf_s("%d", &iMinesAmount);



    SDL_Window* window = SDL_CreateWindow("Une fenetre SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Création du renderer


    Board table = init(size, iMinesAmount); //round(size/difficultie));





    Button play;
    play.width = 250;
    play.height = 75;
    play.text = "DIV";
    play.print = printRectBtn;
    play.isClicked = rectIsClicked;
    play.control = goToGameAdress;



    MMado mainMenu;
    mainMenu.control = controlMenu;
    mainMenu.buttons = (Button*)malloc(sizeof(Button));
    mainMenu.buttons[0] = play;
    mainMenu.nbButtons = 1;
    initMenu(&mainMenu);
    mainMenu.window = window;
    mainMenu.renderer = renderer;
    


    GMado game;
    game.control = gameControl;
    play.adress = &game;

    TTF_Init();

    

    game.window = window;
    game.renderer = renderer;
    game.board = &table;
    


    int running = 1;
    game.active = 0;



    while (running == 1) {


        if (game.active == 1) {
            
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                game.control(&event, game.board);
            }

            displayUI(&game);
        }
        else {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                mainMenu.control(&event, &mainMenu, &game);
            }

            displayMenu(&mainMenu);
        }

        
    }

    return 0;
}



void displayUI(GMado* game) {
    

    Board* board = game->board; 
    SDL_Window* window = game->window;
    SDL_Renderer* renderer = game->renderer;



    SDL_Rect tile;
    SDL_Color fontColor;
    TTF_Font* vera = TTF_OpenFont("fonts/ttf-bitstream-vera-1.10/Vera.ttf", 16);
    SDL_Surface* message;
    char content[2];
    SDL_Texture* indicTile;
    SDL_Surface* flagImg = IMG_Load("img/good_flag.png");
    SDL_Texture* flagTexture = SDL_CreateTextureFromSurface(renderer, flagImg);





    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++)
        {

            tile = { j * 20, i * 20 , 20, 20 };//{position x * la taille d'une case, position y * la taille d'une case, taille de la case (20 * 20)}

            if (board->grid[i * 15 + j].flag == 1) {

                if ((i * 15 + j) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 160, 0, 160, 255);
                }
                else { SDL_SetRenderDrawColor(renderer, 150, 0, 150, 255); }

                SDL_RenderFillRect(renderer, &tile);
                SDL_RenderCopy(renderer, flagTexture, NULL, &tile);
                

            }
            else if (board->grid[i * 15 + j].isVisible == 0) {


                if ((i * 15 + j) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 160, 0, 160, 255);
                }
                else{ SDL_SetRenderDrawColor(renderer, 150, 0, 150, 255); }
                

                SDL_RenderFillRect(renderer, &tile);


            }
            else if (board->grid[i * 15 + j].isVisible == 1) {


                if ((i * 15 + j) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
                }
                else {
                    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
                }
                

                if (board->grid[i * 15 + j].content == 0) {
                    SDL_GetRenderDrawColor(renderer, &fontColor.r, &fontColor.g, &fontColor.b, &fontColor.a);
                }
                else if (board->grid[i * 15 + j].content == 1) {
                    fontColor = { 66,147, 245, 255 };
                }
                else if (board->grid[i * 15 + j].content == 2) {
                    fontColor = {144, 66, 245, 255};
                }
                else if (board->grid[i * 15 + j].content >= 3) {
                    fontColor = { 201, 8, 8, 255 };
                }
                

                sprintf_s(content, "%d", board->grid[i * 15 + j].content);
                SDL_RenderFillRect(renderer, &tile);
                message = TTF_RenderText_Blended(vera, content, fontColor);
                indicTile = SDL_CreateTextureFromSurface(renderer, message);
                SDL_RenderCopy(renderer, indicTile, NULL, &tile);
            }
        }
    }


    SDL_RenderPresent(renderer);


    

    //SDL_WaitEvent(event);
    //SDL_Delay(1000);//pause de 3 secondes

    ////on libère tout
    ////SDL_FreeSurface(message);
    //TTF_CloseFont(vera);
    ////SDL_DestroyTexture(indicTile);
    //SDL_DestroyRenderer(renderer);
    //SDL_DestroyWindow(window);
    //TTF_Quit();
    //SDL_Quit(); 
}



void initMenu(MMado* menu){
    int relativY = GetSystemMetrics(SM_CYSCREEN) / 4;
    for (int i = 0; i < menu->nbButtons; i++) {//sizeof(menu->buttons) / sizeof(Button)
        menu->buttons[i].positionX = GetSystemMetrics(SM_CXSCREEN) / 2 - menu->buttons[i].width;
        menu->buttons[i].positionY = relativY;
        relativY += menu->buttons[i].height + 150;
    }
}

void displayMenu(MMado* menu) {

    SDL_Window* window = menu->window;
    SDL_Renderer* renderer = menu->renderer;



    



    for (int i = 0; i < menu->nbButtons; i++) {//sizeof(menu->buttons) / sizeof(Button)
        menu->buttons[i].print(&menu->buttons[i], menu->renderer);
    }



    SDL_RenderPresent(renderer);




    //SDL_WaitEvent(event);
    //SDL_Delay(1000);//pause de 3 secondes

    ////on libère tout
    ////SDL_FreeSurface(message);
    //TTF_CloseFont(vera);
    ////SDL_DestroyTexture(indicTile);
    //SDL_DestroyRenderer(renderer);
    //SDL_DestroyWindow(window);
    //TTF_Quit();
    //SDL_Quit(); 
}


void printRectBtn(Button* button, SDL_Renderer* renderer) {
    SDL_Rect shape;
    TTF_Font* vera = TTF_OpenFont("fonts/ttf-bitstream-vera-1.10/Vera.ttf", 128);
    SDL_Surface* message;
    SDL_Texture* indicTile;


    shape = { button->positionX, button->positionY , button->width, button->height };
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderFillRect(renderer, &shape);
    message = TTF_RenderText_Blended(vera, button->text, { 201, 8, 8, 255 });
    indicTile = SDL_CreateTextureFromSurface(renderer, message);
    SDL_RenderCopy(renderer, indicTile, NULL, &shape);
}

int rectIsClicked(int x, int y, Button* button){
    if (button->positionX < x < button->positionX + button->width && button->positionY < y < button->positionY + button->height) {
        return 1;
    }
    else {
        return 0;
    }
}



void gameControl(SDL_Event* event, Board* table) {

    int isPlaying;
    isPlaying = 1;
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:

        int x = floor(event->button.x / 20);
        int y = floor(event->button.y / 20);

        if (event->button.button == 1) {
            reveal(table, x, y);
            checkWin(table, x, y, &isPlaying);
        }
        else if (event->button.button == 3) {
            setFlag(table, x, y);
        }
        break;
    }
}


void controlMenu(SDL_Event* event, MMado* menu, GMado* toChange) {
    void* useless;
    useless = &event;
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:

        int x = floor(event->button.x);
        int y = floor(event->button.y);

        if (event->button.button == 1) {
            for (int i = 0; i < menu->nbButtons; i++) {
                if(menu->buttons[i].isClicked(x, y, menu->buttons) == 1) {
                    menu->buttons[i].control(useless, menu->buttons[i].adress, toChange);
                    
                }
            }
        }
        break;
    }
}


void goToGameAdress(void* smth, ...) {//plante netre ok1 et 2
    printf("ok1");
    va_list args;
    va_start(args, smth);
    GMado* game = va_arg(args, GMado*);
    GMado* toChange = va_arg(args, GMado*);
    va_end(args);
    toChange = game;
    game->active = 1; //soucis ici
    printf("ok2");
    //activeOne = game;
}

void goToMenuAdress(GMado* game, MMado* menu, MMado* activeOne) {
    game->active = 0;
    activeOne = menu;
}



Board init(int size, int iMinesAmount) {
    Board table;
    table.size = size;
    table.grid = (Case*)malloc(sizeof(Case) * table.size * table.size);
    table.iMinesAmount = iMinesAmount;
    table.remaining = size * size - iMinesAmount;


    for (int j = 0; j < table.size * table.size; j++) {
        table.grid[j].content = 0;         
        table.grid[j].isVisible = 0;
    };

    
    generateMines(&table);
    return table;
}

void generateMines(Board* oBoard) {
    int iFreeCasesLength = oBoard->size * oBoard->size * 2;
    int* freeCases = (int*)malloc(sizeof(int) * iFreeCasesLength);
    
    for (int i = 0; i < oBoard->size; i++) {
        for (int j = 0; j < oBoard->size; j++) {
            freeCases[i * oBoard->size * 2 + j * 2] = i;
            freeCases[i * oBoard->size * 2 + j * 2 + 1] = j;
        }
    }

    int r = time(NULL);

    for (int i = 0; i < oBoard->iMinesAmount; i++) {
        int tmpLastFreeCase[2] = { freeCases[iFreeCasesLength - 2], freeCases[iFreeCasesLength - 1] };
        int* variable = (int*)realloc(freeCases, sizeof(int) * iFreeCasesLength - 2);
        if (variable != NULL) {
            freeCases = variable;
            iFreeCasesLength -= 2;
            int randomIndex = r % iFreeCasesLength;
            oddToEvenByLower(&randomIndex);
            if (randomIndex != iFreeCasesLength - 1) {
                oBoard->grid[freeCases[randomIndex] + freeCases[randomIndex + 1] * oBoard->size].content = 9;
                freeCases[randomIndex] = tmpLastFreeCase[0];
                freeCases[randomIndex + 1] = tmpLastFreeCase[1];
            }
        }
    }
    free(freeCases);
}

void oddToEvenByLower(int* number) {
    if (*number % 2 == 1) {
        (*number)--;
    }
}

void reveal(Board* table, int x, int y) {
    if (table->grid[x + y * table->size].content != 9 && table->grid[x + y * table->size].isVisible == 0) {
        table->grid[x + y * table->size].isVisible = 1;
        table->remaining -= 1;
        check(table, x, y);
        if (table->grid[x + y * table->size].content == 0) {
            for (int i = -1; i < 2; i++) {  
                if(x+i >=0 && x+i < table->size){
                    for (int j = -1; j < 2; j++) {
                        if(y+j >=0 && y+j < table->size){
                            if(table->grid[(x+i) + (y+j) * table->size].isVisible != 1){
                                reveal(table, x + i, y + j);
                            }
                        }
                    }
                }
            }
        }
    };
}

void check(Board* table, int x, int y) {
    if (table->grid[x + y * table->size].content != 9)
    {
        for (int i = -1; i < 2; i++) {
            if (x + i >= 0 && x + i < table->size) {
                for (int j = -1; j < 2; j++) {
                    if (y + j >= 0 && y + j < table->size) {
                        if (table->grid[(x + i) + (y + j) * table->size].content == 9) {
                            table->grid[x + y * table->size].content += 1;
                        }
                    }
                }
            }
        }
    }
}

void setFlag (Board* table, int x, int y) {
    printf("OK OK");
    if (table->grid[(x + y * table->size)].flag == 1) {
        table->grid[(x + y * table->size)].flag = 0;
    }
    else {
        table->grid[(x + y * table->size)].flag = 1;
    }
}

void checkWin(Board* table, int x, int y, int* playing) {
    if (table->grid[x + y * table->size].content == 9)
    {
        printf("c'est lose\n");
        *playing = 0;
    }
    else if (table->remaining == 0)
    {
        printf("you won, congrats boy\n");
        *playing = 0;
    }
}