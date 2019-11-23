
#include "ControlPoint.h"

using namespace std;

ControlPoint::ControlPoint(int xPos, int yPos, int height, int width, const string& imageFile, ImageHandler *imgHandler){
    //set position (offset from upper left of window)
	this->position.x = xPos;
	this->position.y = yPos;

	//set size of the image
	this->position.h = height;
	this->position.w = width;

    //set image handler for this object
	this->imageHandler = imgHandler;
	//get the Unit image texture from the provided file
	this->image = this->imageHandler->loadImage(imageFile);
}

ControlPoint::~ControlPoint() {
	//delete the image texture that was created for this Tile
	delete this->image;
}

void ControlPoint::render() {
	this->imageHandler->render(this->image, &this->position);
}

const string ControlPoint::getType() {
	return "ControlPoint";
}

int ControlPoint::getX(){
	return position.x;
}

int ControlPoint::getY(){
	return position.y;
}

int ControlPoint::getWidth(){
	return position.w;
}

int ControlPoint::getHeight(){
	return position.h;
}
