#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ImageHandler.h"
#include <iostream>


class ControlPoint{

private:
	int x, y, height, width;
	bool clicked;

public:
    ControlPoint(int xPos, int yPos, int height, int width);
    ~ControlPoint();
    int getX();
    int getY();
    int getWidth();
    int getHeight();

};

#endif