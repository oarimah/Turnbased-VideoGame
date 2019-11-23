#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ImageHandler.h"
#include <iostream>
#include "GameObject.h"

class ControlPoint: public GameObject {

private:
	SDL_Rect position;
	SDL_Texture* image;
	bool clicked;
	ImageHandler* imageHandler;

public:
    ControlPoint(int xPos, int yPos, int height, int width, const std::string& imageFile, ImageHandler *imgHandler);
    ~ControlPoint();
    void render();
    const std::string getType();
    int getX();
    int getY();
    int getWidth();
    int getHeight();

};

#endif