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
	SDL_Rect background;
	bool changed;
	int maxHeight;
	int maxWidth;
	//create font to use to display text
	TTF_Font* textFont = TTF_OpenFont("Fonts/CaviarDreams_Bold.ttf", 32);

	//set color of the text
	SDL_Color textColor = { 255,255,255 };

	SDL_Renderer* renderer;
	
	//background image for text display box
	SDL_Texture* backgroundDisplay;


public:
	TextDisplay(const std::string& inputText, int xPos, int yPos, int height, int width, SDL_Renderer* renderHere);
	~TextDisplay();
	const bool getChanged();
	void display(const std::string& newText);
	void render();
	const std::string getType();

};

#endif
