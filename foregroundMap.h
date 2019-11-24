#ifndef FOREGROUNDMAP_H
#define FOREGROUNDMAP_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "ImageHandler.h"
#include "Tile.h"
#include "UnitFactory.h"
#include <iostream>
#include <string>
#include "TextDisplay.h"
#include "Player.h"

class foregroundMap: public GameObject {

private:

	ImageHandler* imageHandler;
	TextDisplay* displayBox;
	int width, height, numTilesWide, numTilesHigh;
	std::vector<std::vector<Unit*>*> map;
	std::vector<ControlPoint *>* cp;
	Player* player1, *player2;
	Unit* unitClicked;
	int clickedX, clickedY;
	std::vector<ControlPoint*>* controlPts;

public:

	foregroundMap(int tileWidth, int tileHeight, int numRow, int numColumn, ImageHandler* imgHandler,

	TextDisplay* textDisplay, Player* player1, Player* player2, std::vector<ControlPoint *>* cp);


	~foregroundMap();

	void render();

	void handleEvent(const SDL_Event* event, int player);

	const std::string getType();

};

#endif
