#ifndef BACKGROUNDMAP_H
#define BACKGROUNDMAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ImageHandler.h"
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
    SDL_Texture* texture;
    SDL_Rect* rect;

public:
	backgroundMap(int tileHeight, int tileWidth, int numRows, int numColumns, ImageHandler *imgHandler);
	~backgroundMap();
	void render();
};


#endif
