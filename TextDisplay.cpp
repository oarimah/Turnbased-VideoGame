#include "TextDisplay.h"

TextDisplay::TextDisplay(const std::string& inputText, int xPos, int yPos, int height, int width, SDL_Renderer* renderHere)
{
	this->renderer = renderHere;
	this->changed = false;
	this->position.x = xPos;
	this->position.y = yPos;
	this->position.h = height;
	this->position.w = width;

	//create surface from text, font and colour
	SDL_Surface* textSurface;
	textSurface = TTF_RenderText_Blended_Wrapped(textFont, inputText.c_str(), textColor, 500);

	//convert surface to texture and store 
	this->currentDisplay = SDL_CreateTextureFromSurface(this->renderer, textSurface);
}

TextDisplay::~TextDisplay()
{

	delete this->currentDisplay;
	delete this->textFont;

}

const bool TextDisplay::getChanged()
{
	return this->changed;
}

void TextDisplay::display(const std::string& newText)
{
	//create new surface from text, font and colour
	SDL_Surface* textSurface;
	textSurface = TTF_RenderText_Blended_Wrapped(textFont, newText.c_str(), textColor, 500);

	//convert surface to texture and store 
	this->currentDisplay = SDL_CreateTextureFromSurface(this->renderer, textSurface);

	//mark changed to true
	changed = true;
}

void TextDisplay::render()
{
	SDL_RenderCopy(this->renderer, this->currentDisplay, NULL, &this->position);

}

const std::string TextDisplay::getType()
{
	return "TextDisplay";
}
