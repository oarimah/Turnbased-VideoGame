#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Player.h"
#include <vector>
#include "ImageHandler.h"
#include "TextDisplay.h"
#include "InfoButtonHandler.h"
#include "backgroundMap.h"
#include "foregroundMap.h"
#include "ControlPoint.h"
#include "Button.h"
#include <iostream>
#include "SpecialAbilities.h"




class Game {
private: 
	
	Player* players[2];
	int currentPlayerIndex;
	backgroundMap* bgMap;
	foregroundMap* fgMap;
	bool isRunning;
	int height, width, tileHeight, tileWidth;
	ImageHandler* imageHandler;
	SDL_Renderer* renderer;
	TextDisplay* displayBox;
	Button* continueButton;
	Button* ruleButton;
	std::vector<ControlPoint *> arr;
	SpecialAbilities* sa;

	void rules();
	void doWinScreen(int playerWins);
	void doCreditScreen();

public:

	Game(int numTilesHigh, int numTilesWide, int tileWidth, int tileHeight);
	~Game();
	int init();
	void eventHandler(const SDL_Event* event);
	void render();
    void renderClear();
   	void renderRepresent();
	bool running();

};

#endif
