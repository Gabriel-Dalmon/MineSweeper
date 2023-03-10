#ifndef UTILS_SWITCHES_H_INCLUDED
#define UTILS_SWITCHES_H_INCLUDED

#include "global.h"

void switchToMSGameEasy(MainScreen* oMainScreen);
void switchToMSGameNormal(MainScreen* oMainScreen);
void switchToMSGameHard(MainScreen* oMainScreen);
void switchToMSGame(MainScreen* oMainScreen, int difficulty);
void switchToMainMenu(MainScreen* oMainScreen);
void switchToEndPopup(MainScreen* oMainScreen);
void switchToDiffSelectMenu(MainScreen* oMainScreen);
void quitApp(MainScreen* oMainScreen);

#endif