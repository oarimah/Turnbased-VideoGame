#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Player.h"
#include "TextDisplay.h"
#include "InfoButtonHandler.h"
#include "backgroundMap.h"
#include "foregroundMap.h"
#include "Button.h"
#include <iostream>




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
