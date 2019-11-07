#ifndef BACKGROUNDMAP_H
#define BACKGROUNDMAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ImageHandler.h"
#include "Tile.h"
//#include "unit.h"
#include <iostream>
#include "GameObject.h"

class Map: public GameObject{

private:
	SDL_Rect position;
	SDL_Texture* image;
	ImageHandler* imageHandler;

public:
	Map(int tileHeight, int tileWidth, int height, int width, const std::string& imageFile);
	~Map();
	void render();

};


#endif
