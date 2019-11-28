// backgroundMap.cpp
#include "backgroundMap.h"

/**@brief Background map class describes the background of the game map and its image
@author Jake Nemiroff
@author Oluwadarasimi Ogunshote
details This class creates an image of the map and handles rendering the image to the game window 
	
*/



/**@brief Constructor for a new background map object
details This function takes size of tiles and number of tiles high and wide for the map to be created. 
	These parameters are saved for future use. The image handler is passed in as well and it is used 
	to create a texture from the background map image and render it when needed.

@param 	tileHeight int width of the individual tiles in pixels
@param 	tileWidth int width of the individual tiles in pixels
@param 	numRows int number of rows in the map
@param 	numColumns int number of columns in the map
@param 	imgHandler a pointer to the image handler to use for rendering

@return a new game object
	
*/
backgroundMap::backgroundMap(int tileHeight, int tileWidth, int numRows,
		int numColumns, ImageHandler *imgHandler) {

	//set position (offset from upper left of window)
	this->tileHeight = tileHeight;
	this->tileWidth = tileWidth;

	this->numRows = numRows;

	this->numColumns = numColumns;

	//set image handler for this object
	this->imageHandler = imgHandler;

    SDL_Texture* texture = this->imageHandler->loadImage("Background/backgroundMap.png");

    this-> rect = new SDL_Rect;

    rect->x = 0;
    rect->y = 0;

    rect->h = tileHeight * numRows;
    rect->w = tileWidth * numColumns;

    this->texture = texture;  
}


/**@brief destructor for a new background map object
details This function dynamically deallocates the position rectangle used for the map size.
        This is the only dynamically created object in this class

@param none

@return none
	
*/
backgroundMap::~backgroundMap() {

    delete this->rect;
}

/**@brief function that renders the image stored as a background map
details This function used the image handler that is stored to render 
	the image texter to the defined location on the game window

@param none

@return none
	
*/
void backgroundMap::render() {
	// render the picture
    this->imageHandler->render(this->texture, this->rect);
}
