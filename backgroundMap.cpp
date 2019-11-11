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

	for (int i = 0; i < numRows; i++) {
		this->tile.push_back(new std::vector<Tile*>);
		for (int j = 0; j < numColumns; j++) {
			this->tile[i]->push_back(
					new Tile(i * tileWidth, j * tileHeight, tileHeight,
							tileWidth, "grass.png", this->imageHandler));
		}
	}
}

backgroundMap::~backgroundMap() {
	for (int i = 0; i < numRows; i++)
		delete this->tile[i];
}

void backgroundMap::render() {
	// render the picture
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numColumns; j++)
			this->tile[i][0][j]->render();
}
