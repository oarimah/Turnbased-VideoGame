#include "TextDisplay.h"

/**@brief This class defines a display box within the game window which contains dynamically changeable text
@author Carolyn Owen
details The class takes c strings, converts them to SDL image format and displays them to the desired location on the game window.
	Functions exist to initialize the box with text, render the image to the screen, check if the text being displayed has changed,
	get the type of object that it is and safely destroy the display box.
*/


/**@brief Constructor for a new text display box object
details This function takes initial c string text, position and renderer and converts the text to an image using the renderer given,
	then displaying it to the location specified. The background of the display box is defined within the constructor, rather than in the 
	passed parameters. The size of the text image will be defined from a query to the SDL surface object created from the input text.
	Size of text, font and text colour are defined within the header file.
@param  
	
*/
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


/**@brief Destructor for a new text display box object
details This function safely deletes a text display box by deleting the current display image and font which were dynamically allocated

@param none
@return none

*/
TextDisplay::~TextDisplay()
{

	delete this->currentDisplay;
	delete this->textFont;

}

/**@brief Getter to check if the text of the display box has changed
details This function returns a boolean value representing whether or not the text displayed has changed
@param  none
@return constant bool value representing whether or not the text has changed 
	
*/
const bool TextDisplay::getChanged()
{
	return this->changed;
}

/**@brief Changes the text to be displayed in the text display box object
details This function takes the input string, converts to an SDL texture with a size determined by 
	the size of the input text (if the text is larger than the size of the display box, the size will be set to equal 
	the size of the display box) and displays it to the area defined by the text display box
@param  Text string to display
@return none
	
*/
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

/**@brief Renders the display box to the game window
details This function renders the background image of the display box and then the current text image overtop of it

@param  none
@return none
	
*/
void TextDisplay::render()
{
	SDL_RenderCopy(this->renderer, this->backgroundDisplay, NULL, &this->background);

	SDL_RenderCopy(this->renderer, this->currentDisplay, NULL, &this->position);

}

/**@brief Getter for type of object
details This function returns the fact that the object is a text display box as a string

@param  none
@return constant string text display to show that the object is a text display box
	
*/
const std::string TextDisplay::getType()
{
	return "TextDisplay";
}
