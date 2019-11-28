
#include "ControlPoint.h"

using namespace std;

/**@brief ControlPoint class defines and manages all control points on the map
@author Carolyn Owen
@author Jake Nemiroff
@author Oluwadarasimi Ogunshote
details This class stores the attributes for the position and size of control points
	It also allows for the retrieval of these attributes 
	
*/

/**@brief Constructor for a new ControlPoint object
details This function takes the position and size information of the control point and stores them
        for their use in game

@param 	xPos offset from the left corner in pixels
@param 	yPos offset from the top corner in pixels
@param 	width width of the control point in pixels
@param 	height height of the control point in pixels

@return a new ControlPoint object
	
*/

ControlPoint::ControlPoint(int xPos, int yPos, int height, int width){
    //set position (offset from upper left of window)
	this->x = xPos;
	this->y = yPos;

	//set size of the control point
	this->height = height;
	this->width = width;

}

/**@brief destructor for a new ControlPoint object
details This function deletes the ControlPoint object that calls it

@param 	none

@return none
	
*/

ControlPoint::~ControlPoint() {
	
}

/**@brief function that retrieves the x position of the object
details This function returns the offset of the control point from the left as an integer

@param 	none

@return the x position of the object
	
*/

int ControlPoint::getX(){
	return this->x;
}

/**@brief function that retrieves the y position of the object
details This function returns the offset of the control point from the top as an integer

@param 	none

@return the y position of the object
	
*/

int ControlPoint::getY(){
	return this->y;
}

/**@brief function that retrieves the width of the object
details This function returns the width of the control point object as in integer

@param 	none

@return the width of the object
	
*/

int ControlPoint::getWidth(){
	return this->width;
}

/**@brief function that retrieves the height of the object
details This function returns the height of the control point object as in integer

@param 	none

@return the height of the object
	
*/

int ControlPoint::getHeight(){
	return this->height;
}
