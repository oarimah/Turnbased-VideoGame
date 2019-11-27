#include "ImageHandler.h"

//class to take image file, and return texture when asked



ImageHandler::ImageHandler(SDL_Renderer* renderHere) {
	this->renderer = renderHere;
}

ImageHandler::~ImageHandler() {

}

//static function allows this to work like a singleton so can be called without instantiation
SDL_Texture* ImageHandler::loadImage(const std::string& imageFile) {

	//create surface first from image file
	SDL_Surface* surface = IMG_Load(imageFile.c_str());

	//then create texture from surface created and return to user
	SDL_Texture* text = SDL_CreateTextureFromSurface(this->renderer, surface);
	
	return text;
}


//renders the texture to the window
void ImageHandler::render(SDL_Texture* image, SDL_Rect* position) {

	//render the image given to the location rectangle provided
	SDL_RenderCopy(this->renderer, image, NULL, position);


}