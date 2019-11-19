#include "TextDisplay.h"

TextDisplay::TextDisplay(const std::string& inputText, int xPos, int yPos, int height, int width, SDL_Renderer* renderHere)
{
	this->renderer = renderHere;
	this->changed = false;
	
	//add extra to x and y positions to allow proper placement over background image
	this->position.x = xPos + 20;
	this->position.y = yPos + 20;
	this->maxHeight = height;
	this->maxWidth = width;

	//create surface from text, font and colour
	SDL_Surface* textSurface;
	textSurface = TTF_RenderText_Blended_Wrapped(textFont, inputText.c_str(), textColor, 500);

	//convert surface to texture and store 
	this->currentDisplay = SDL_CreateTextureFromSurface(this->renderer, textSurface);
	
	//create background image to use under text
	
	SDL_Surface* surface = IMG_Load("Buttons/button_brown_vertical.png");

	//set size of background based on input
	this->background.x = xPos;
	this->background.y = yPos;
	this->background.h = height;
	this->background.w = width;
	
	//then create texture from surface created and return to user
	this->backgroundDisplay = SDL_CreateTextureFromSurface(this->renderer, surface);
	
	
	//query the texture to determine size of text
	int textHeight = 0;
	int textWidth = 0;
	
	SDL_QueryTexture(this->currentDisplay, NULL, NULL, &textWidth, &textHeight);
	
	if (textHeight <= this->maxHeight){
	this->position.h = textHeight;
}
	else{
		
		this->position.h = maxHeight;
	}
	
	if (textWidth <= this->maxWidth){
	this->position.w = textWidth;
}
else{
	this->position.w = maxWidth;
}
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
	
	//query the texture to determine size of text
	int textHeight = 0;
	int textWidth = 0;
	
	SDL_QueryTexture(this->currentDisplay, NULL, NULL, &textWidth, &textHeight);
	if (textHeight <= this->maxHeight){
	this->position.h = textHeight;
}
	else{
		this->position.h = maxHeight;
	}
	
	if (textWidth <= this->maxWidth){
	
	this->position.w = textWidth;
}
else{
	
	this->position.w = maxWidth;
}

	//mark changed to true
	changed = true;
}

void TextDisplay::render()
{
	SDL_RenderCopy(this->renderer, this->backgroundDisplay, NULL, &this->background);

	SDL_RenderCopy(this->renderer, this->currentDisplay, NULL, &this->position);

}

const std::string TextDisplay::getType()
{
	return "TextDisplay";
}
