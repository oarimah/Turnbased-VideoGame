#include "EraseButtonHandler.h"
#include <iterator>

EraseButtonHandler::EraseButtonHandler(int* intToErase)
{
	//set int to erase pointer to location input
	this->intErase = intToErase;

	//set both other pointers to null to indicate that we're not erasing those things
	this->stringErase = NULL;
	this->vectorErase = NULL;
}

EraseButtonHandler::EraseButtonHandler(std::vector<GameObject*>* vectorToErase)
{
	//set vector to erase pointer to location input
	this->vectorErase = vectorToErase;

	//set both other pointers to null to indicate that we're not erasing those things
	this->stringErase = NULL;
	this->intErase = NULL;

}

EraseButtonHandler::EraseButtonHandler(std::string* stringToErase)
{

	//set string to erase pointer to location input
	this->stringErase = stringToErase;

	//set both other pointers to null to indicate that we're not erasing those things
	this->vectorErase = NULL;
	this->intErase = NULL;
}

EraseButtonHandler::~EraseButtonHandler()
{

}

void EraseButtonHandler::handleEvent(const SDL_Event* event)
{

	//when clicked, erase whatever is stored in the to be erased pointer 
	if (event->type == SDL_MOUSEBUTTONUP) {


		if (this->intErase != NULL) {
			*this->intErase = 0;
		}

		else if (this->stringErase != NULL) {
			*this->stringErase = "";
		}

		else if (this->vectorErase != NULL) {
			 
			//get a constant iterator pointing to start and end of vector for the vector stored at the pointed to location 
			std::vector<GameObject*>::const_iterator eraseFirst = this->vectorErase->cbegin();
			std::vector<GameObject*>::const_iterator eraseLast = this->vectorErase->cend();

			//call vector's erase function on the entire range of the vector from first to last 
			this->vectorErase->erase(eraseFirst, eraseLast);
		}
		
	}
}
