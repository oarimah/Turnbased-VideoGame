#include "Tile.h"


Tile::Tile(int xPos, int yPos, int height, int width, const std::string& imageFile, ImageHandler *imgHandler) {

    //set position (offset from upper left of window)
    this->position.x = xPos;
    this->position.y = yPos;

    //set size of the image
    this->position.h = height;
    this->position.w = width;
    
    //set image handler for this object
    this->imageHandler = imgHandler;
    //get the Tile texture from the provided file
    this->image = this->imageHandler->loadImage(imageFile);

    //nothing has been clicked yet, set to false
    this->clicked = false;
}

Tile::~Tile()
{

    //delete the image texture that was created for this Tile
    delete this->image;

    //do not delete Tile event as not unique to this Tile
}

const SDL_Rect* Tile::getPosition()
{
    return &this->position;
}

void Tile::changePosition(int newX, int newY)
{

    //change the x and y values of the position rectangle to reflect new values 
    this->position.x = newX;
    this->position.y = newY;

}

const bool Tile::isClicked()
{
    return this->clicked;
}

void Tile::changeClicked(bool value) {

    this->clicked = value;
    return;

}

void Tile::changeImage(const std::string& imageFile) {

    SDL_Texture *temp = this->imageHandler->loadImage(imageFile.c_str());
    this->image = temp;

}


void Tile::render() {

    this->imageHandler->render(this->image, &this->position);
}

const std::string Tile::getType()
{
    return "Tile";
}
