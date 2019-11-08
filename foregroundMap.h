#ifndef FOREGROUNDMAP_H
#define FOREGROUNDMAP_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "ImageHandler.h"
#include "Tile.h"
#include "Unit.h"
#include <iostream>
#include "TextDisplay.h"
#include "Player.h"

class foregroundMap: public GameObject{

private:

	ImageHandler* imageHandler;
	TextDisplay* displayBox;
	int width, height, numTilesWide, numTilesHigh;
	Unit* map[20][20];
	Player* player1, *player2;
	Unit* unitClicked;
	int clickedX, clickedY;



public:

	foregroundMap(int tileWidth, int tileHeight, ImageHandler* imgHandler, TextDisplay* textDisplay, Player* player1, Player* player2);
	
	~foregroundMap();

	void render();

    void handleEvent(const SDL_Event* event, int player);
    
    const std::string getType();

};


#endif
