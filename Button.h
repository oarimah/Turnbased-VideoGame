#ifndef BUTTON_H
#define BUTTON_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ImageHandler.h"
#include "ButtonEventHandler.h"
#include <iostream>
#include "GameObject.h"


class Button: public GameObject{

private:
	SDL_Rect position;
	SDL_Texture* image;
	ButtonEventHandler* eventHandler;
	bool clicked;
	ImageHandler* imageHandler;

public:
	Button(int xPos, int yPos, int height, int width, ButtonEventHandler* handler, const std::string& imageFile, ImageHandler* imgHandler);
	~Button();
	const SDL_Rect* getPosition();
	void changePosition(int newX, int newY);
	const bool isClicked();
	void handleEvent(const SDL_Event* newEvent);
	void changeImage(const std::string& imageFile);
	void render();
	const std::string getType();
	void changeClicked(bool value);
};


#endif // !BUTTON_H
