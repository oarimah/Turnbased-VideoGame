/*#include "SelectButtonHandler.h"



SelectButtonHandler::SelectButtonHandler(const std::string& changeImageToFile)
{
	//store name of image file to be used when button clicked
	this->changeImageFile = changeImageToFile;
}

SelectButtonHandler::~SelectButtonHandler()
{


}

void SelectButtonHandler::handleEvent(const SDL_Event* event)
{

	//when clicked, change image of the button to the new image 
	if (event->type == SDL_MOUSEBUTTONUP) {

		self->changeImage(this->changeImageFile);
	
	}
}
*/