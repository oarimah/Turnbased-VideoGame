
#include "Button.h"

/**@brief Class defines a button that is displayed to the game screen and contains a handler to deal with events on the button
@author Carolyn Owen
details This class has an image that displays to a given point on the screen. When the button is clicked on, it passes the event to
	the event handler that the button contains. Because of changeable handlers, the button can have different behaviours on clicking.

*/


/**@brief Constructor for a button object
details This function takes location information, a pointer to a button event handler, a string for the image to display
	as the button and an image handler object. The location information is saved for future rendering, as is the image handler.
	The image file is sent to the image handler to create and store a texture of the image file, event handler is saved and bool
	value to represent the button being clicked is set to false


@param  xPos,int x position which is the offset from the left of the screen in pixels
@param 	yPos, int y position which is the offset from the top of the screen in pixels
@param	height,int height which is the height of the image to display as the button in pixels
@param	width, int width which is the width of the image to display as the button in pixels
@param 	handler, pointer to button event handler to use when the button is clicked
@param	imageFile, constant string reference which is the name of the png file of the button image
@param 	imgHandler, pointer to image handler object to use to load and render the image

@return a new initialized button object

*/
Button::Button(int xPos, int yPos, int height, int width, ButtonEventHandler* handler, const std::string& imageFile, ImageHandler *imgHandler) {

    //set position (offset from upper left of window)
    this->position.x = xPos;
    this->position.y = yPos;

    //set size of the image
    this->position.h = height;
    this->position.w = width;

    //set image handler for this object
    this->imageHandler = imgHandler;
    //get the button texture from the provided file
    this->image = this->imageHandler->loadImage(imageFile);

    //point event handler to given button event (this will determine button behaviour)
    this->eventHandler = handler;

    //nothing has been clicked yet, set to false
    this->clicked = false;
}


/**@brief Destructor for a button object
details This function deallocates the button's image texture, which is the only dynamically allocated object created by the button

@param  none
@return none, just delete the image of the button

*/
Button::~Button()
{

    //delete the image texture that was created for this button
    delete this->image;

    //do not delete button event as not unique to this button
}


/**@brief getter for an SDL rectangle pointer representing the button's location
details This function returns a constant pointer to an SDL rectangle which contains the button's x and y position,
	as well as width and height

@param  none
@return a pointer to the position

*/
const SDL_Rect* Button::getPosition()
{
    return &this->position;
}


/**@brief Function to change the position of the button
details This function updates the x and y offsets of the button on the game window. The x and y positions are in pixels.
	The next time that the button is rendered, it will relocate to the new position.

@param  int newX position representing the offset in pixels from the left of the window
@param 	int newY position representing the offset in pixels from the top of the window
@return	none, just change the position

*/
void Button::changePosition(int newX, int newY)
{

    //change the x and y values of the position rectangle to reflect new values
    this->position.x = newX;
    this->position.y = newY;

}


/**@brief Getter for bool value representing the fact that the button has been clicked
details This function returns a constant boolean value which is stored in the button.
	The value is changed to true if the button has been clicked.

@param  none
@return clicked, a constant boolean value

*/
const bool Button::isClicked()
{
    return this->clicked;
}


/**@brief Event handler to call when the button has an event happening over it
details This function takes an SDL event which has happened over the location of the button.
	It checks to see if the event was a click. If so, clicked bool value is set to true and the button event handler
	stored in the button is called to handle it however is defined by the type of button event handler object stored.

@param  newEvent, constant pointer to SDL event
@return none

*/
void Button::handleEvent(const SDL_Event* newEvent)
{
    if (newEvent->button.type == SDL_MOUSEBUTTONUP) {

        if (this->clicked) {
            this->clicked = false;
        }

        else {
            this->clicked = true;
        }

    }
    //call the event handler stored in this button

    this->eventHandler->handleEvent(newEvent);

}


/**@brief Function changes the value of the clicked boolean of the button
details This function takes a new boolean value which is stored in the button's clicked member variable.

@param  value, boolean value to change to
@return none

*/
void Button::changeClicked(bool value) {

    this->clicked = value;
    return;

}


/**@brief Function changes the image that represents the button
details This function takes a constant string reference which represents the png file to change the image to. The function calls the button's
	image handler to load a texture for this new image file and then stores it within the button's image variable.

@param  imageFile, constant string reference of the image file's name
@return none

*/
void Button::changeImage(const std::string& imageFile) {

    SDL_Texture *temp = this->imageHandler->loadImage(imageFile.c_str());
    this->image = temp;

}

/**@brief Function renders the button to the game window
details This function uses the button's stored image handler to render the image in the button to the button's location.

@param  none
@return none, just render the image at this position

*/
void Button::render() {

    this->imageHandler->render(this->image, &this->position);
}


/**@brief Getter for the object type
details This function returns a constant string letting the caller know that the object is a button.
	This fulfils the requirement that this is implemented for all game object subclasses.

@param  none
@return "Button", constant string

*/
const std::string Button::getType()
{
    return "Button";
}
