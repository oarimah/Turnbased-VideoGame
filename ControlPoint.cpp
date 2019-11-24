
#include "ControlPoint.h"

using namespace std;

ControlPoint::ControlPoint(int xPos, int yPos, int height, int width){
    //set position (offset from upper left of window)
	this->x = xPos;
	this->y = yPos;

	//set size of the control point
	this->height = height;
	this->width = width;

}

ControlPoint::~ControlPoint() {
	
}


int ControlPoint::getX(){
	return this->x;
}

int ControlPoint::getY(){
	return this->y;
}

int ControlPoint::getWidth(){
	return this->width;
}

int ControlPoint::getHeight(){
	return this->height;
}
