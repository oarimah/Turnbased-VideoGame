#include "ImageHandler.h"

/**@brief Image Handler class manages basic image functions for other classes
@author Carolyn Owen
details This class takes care of loading and rendering images from png files.  
	
*/




/**@brief Constructor for a new image handler object
details This function takes an SDL renderer to use when rendering images. 
@param  SDL renderer pointer for window that will be displayed to

@return a new image handler object
	
*/
ImageHandler::ImageHandler(SDL_Renderer* renderHere) {
	this->renderer = renderHere;
}

/**@brief Destructor for an image handler object
details This function safely deletes all dynamically allocated objects. 
	There are no allocated objects created by this class, so the function is empty.

@param  none
@return none
	
*/
ImageHandler::~ImageHandler() {

}

/**@brief Creates an SDL Texture for a given image file
details This function takes initial png image file, converts it to an SDL surface and uses the renderer to create a texture object to return.
 
@param  constant string reference of the image file name

@return SDL texture pointer to created texture for caller to use
	
*/
SDL_Texture* ImageHandler::loadImage(const std::string& imageFile) {

	//create surface first from image file
	SDL_Surface* surface = IMG_Load(imageFile.c_str());

	//then create texture from surface created and return to user
	SDL_Texture* text = SDL_CreateTextureFromSurface(this->renderer, surface);
	
	return text;
}


/**@brief Renders a texture to the given position on the game window
details This function takes an SDL texture pointer and SDL rectangle pointer and uses the renderer to display the texture image 
	to the location given in the rectangle. The entire texture will be rendered by this function.

@param  SDL rectangle pointer containing location information for the area to display to 
@param 	SDL texture pointer representing the image to display

@return none
	
*/
void ImageHandler::render(SDL_Texture* image, SDL_Rect* position) {

	//render the image given to the location rectangle provided
	SDL_RenderCopy(this->renderer, image, NULL, position);


}