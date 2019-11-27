// backgroundMap.cpp
#include "backgroundMap.h"

backgroundMap::backgroundMap(int tileHeight, int tileWidth, int numRows,
		int numColumns, ImageHandler *imgHandler) {

	//set position (offset from upper left of window)
	this->tileHeight = tileHeight;
	this->tileWidth = tileWidth;

	this->numRows = numRows;

	this->numColumns = numColumns;

	//set image handler for this object
	this->imageHandler = imgHandler;

    SDL_Texture* texture = this->imageHandler->loadImage("Background/backgroundMap.png");

    this-> rect = new SDL_Rect;

    rect->x = 0;
    rect->y = 0;

    rect->h = tileHeight * numRows;
    rect->w = tileWidth * numColumns;

    this->texture = texture;  
}

backgroundMap::~backgroundMap() {

    delete this->rect;
}

void backgroundMap::render() {
	// render the picture
    this->imageHandler->render(this->texture, this->rect);
}
