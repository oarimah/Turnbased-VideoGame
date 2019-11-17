#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ImageHandler.h"
#include <iostream>
#include "GameObject.h"

class Tile: public GameObject{

private:
	SDL_Rect position;
	SDL_Texture* image;
	bool clicked;
	ImageHandler* imageHandler;

public:
	Tile(int xPos, int yPos, int height, int width, const std::string& imageFile, ImageHandler* imgHandler);
	~Tile();
	const SDL_Rect* getPosition();
	void changePosition(int newX, int newY);
	const bool isClicked();
	void changeImage(const std::string& imageFile);
	void render();
	const std::string getType();
	void changeClicked(bool value);
};


#endif
