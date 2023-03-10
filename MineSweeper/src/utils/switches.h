#ifndef UTILS_SWITCHES_H_INCLUDED
#define UTILS_SWITCHES_H_INCLUDED

#include "global.h"

/**
* Calls the switchToMSGame with difficulty parameter = 1.
* @param MainScreen* oMainScreen - Main Screen to update with the new App/Screen state.
*/
void switchToMSGameEasy(MainScreen* oMainScreen);

/**
* Calls the switchToMSGame with difficulty parameter = 2.
* @param MainScreen* oMainScreen - Main Screen to update with the new App/Screen state.
*/
void switchToMSGameNormal(MainScreen* oMainScreen);

/**
* Calls the switchToMSGame with difficulty parameter = 3.
* @param MainScreen* oMainScreen - Main Screen to update with the new App/Screen state.
*/
void switchToMSGameHard(MainScreen* oMainScreen);

/**
* Switches the MainScreen's state to MSGame state.
* @param MainScreen* oMainScreen - Main Screen to update with the new state.
* @param int difficulty - defines the size of the MS Game Board and the amount of mines.
*/
void switchToMSGame(MainScreen* oMainScreen, int difficulty);

/**
* Switches the MainScreen's state to MSGame state.
* @param MainScreen* oMainScreen - Main Screen to update with the new state.
*/
void switchToMainMenu(MainScreen* oMainScreen);

/**
* Switches the MainScreen's state to MainMenu state.
* @param MainScreen* oMainScreen - Main Screen to update with the new state.
*/
void switchToEndPopup(MainScreen* oMainScreen);

/**
* Switches the MainScreen's state to the Popup state. Will keep the previous state in background
* @param MainScreen* oMainScreen - Main Screen to update with the new state.
*/
void switchToDiffSelectMenu(MainScreen* oMainScreen);

/**
* Switches the MainScreen's state to Difficulty Selection Menu state.
* @param MainScreen* oMainScreen - Main Screen to update with the new state.
*/
void quitApp(MainScreen* oMainScreen);

#endif