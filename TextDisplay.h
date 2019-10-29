#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "ImageHandler.h"

class TextDisplay {

private:
	SDL_Texture* currentDisplay;
	SDL_Rect position;
	bool changed;

	//create font to use to display text
	TTF_Font* textFont = TTF_OpenFont("Roboto-Bold.ttf", 12);

	//set color of the text
	SDL_Color textColor = { 255, 255, 255 };

	SDL_Renderer* renderer;


public:
	TextDisplay(const std::string& inputText, int xPos, int yPos, int height, int width, SDL_Renderer* renderHere);
	~TextDisplay();
	const bool getChanged();
	void display(const std::string& newText);
	void render();
	const std::string getType();

};

#endif
