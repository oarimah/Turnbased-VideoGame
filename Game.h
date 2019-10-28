#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//#include "Player.h"
#include "TextDisplay.h"
//#include "Map.h"
#include <iostream>


//define static variables for game class's tile height and width
static const int TILE_HEIGHT = 32;
static const int TILE_WIDTH = 32;


class Game {
private: 

	//Player* players[];
	//Map* backgroundMap, foregroundMap;
	bool isRunning;
	int height, width;
	ImageHandler* imageHandler;
	SDL_Renderer* renderer;
	TextDisplay* displayBox;

public:

	Game(int numTilesHigh, int numTilesWide);
	~Game();
	int init();
	void eventHandler(const SDL_Event* event);
	void render();
	const bool running();

};

#endif