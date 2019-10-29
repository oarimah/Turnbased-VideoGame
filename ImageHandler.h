#ifndef IMAGE_HANDLER_H
#define IMAGE_HANDLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


class ImageHandler {

private:
	SDL_Renderer* renderer;


public:
	ImageHandler(SDL_Renderer *renderHere);
	~ImageHandler();
	SDL_Texture* loadImage(const std::string& imageFile);
	void render( SDL_Texture* image,  SDL_Rect* position);

};

#endif
