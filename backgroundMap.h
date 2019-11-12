#ifndef BACKGROUNDMAP_H
#define BACKGROUNDMAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ImageHandler.h"
#include "Tile.h"
#include <iostream>
#include "GameObject.h"
#include <vector>

class backgroundMap{

private:

    ImageHandler* imageHandler;
    int tileHeight;
    int tileWidth;
    int numRows;
    int numColumns;
    std::vector<std::vector<Tile*>*> tile;

public:
	backgroundMap(int tileHeight, int tileWidth, int numRows, int numColumns, ImageHandler *imgHandler);
	~backgroundMap();
	void render();
    std::string flipTileColour(std::string tileName);

};


#endif
