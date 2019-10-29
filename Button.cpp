
#include "Button.h"







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

	Button::~Button()
	{

		//delete the image texture that was created for this button
		delete this->image;

		//do not delete button event as not unique to this button
	}

	const SDL_Rect* Button::getPosition()
	{
		return &this->position;
	}

	void Button::changePosition(int newX, int newY)
	{

		//change the x and y values of the position rectangle to reflect new values 
		this->position.x = newX;
		this->position.y = newY;

	}

	const bool Button::isClicked()
	{
		return this->clicked;
	}

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

	void Button::changeClicked(bool value) {

		this->clicked = value;
		return;

	}

	void Button::changeImage(const std::string& imageFile) {

		SDL_Texture *temp = this->imageHandler->loadImage(imageFile.c_str());
		this->image = temp;
	
	}


	void Button::render() {

		this->imageHandler->render(this->image, &this->position);
	}

	const std::string Button::getType()
	{
		return "Button";
	}
