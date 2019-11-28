#include "EraseButtonHandler.h"
#include <iterator>


/**@brief Class defines a handler to erase something when the owning button is invoked
@author Carolyn Owen
details This class can erase an integer, string or vector when called on.
	It is owned by a button object and the type of object to erase is defined on construction.

*/


/**@brief Constructor for a button event handler to erase an integer
details This function takes a pointer to an integer to be erased when the handler is called.
	When it is called, the integer pointed at is deleted. The member variables for strings and vectors
	are set to NULL to indicate that it is not erasing these types of things.

@param  intToErase, pointer to the int to erase

@return a new erase button handler object

*/
EraseButtonHandler::EraseButtonHandler(int* intToErase)
{
    //set int to erase pointer to location input
    this->intErase = intToErase;

    //set both other pointers to null to indicate that we're not erasing those things
    this->stringErase = NULL;
    this->vectorErase = NULL;
}


/**@brief Constructor for a button event handler to erase a vector
details This function takes a pointer to a vector to be emptied when the handler is called.
	When it is called, the contents of the vector pointed at are deleted. The member variables for strings and ints
	are set to NULL to indicate that it is not erasing these types of things.

@param  vectorToErase, pointer to the vector to erase

@return a new erase button handler object

*/
EraseButtonHandler::EraseButtonHandler(std::vector<GameObject*>* vectorToErase)
{
    //set vector to erase pointer to location input
    this->vectorErase = vectorToErase;

    //set both other pointers to null to indicate that we're not erasing those things
    this->stringErase = NULL;
    this->intErase = NULL;

}


/**@brief Constructor for a button event handler to erase a string
details This function takes a pointer to a string to be erased when the handler is called.
	When it is called, the string pointed at is deleted. The member variables for ints and vectors
	are set to NULL to indicate that it is not erasing these types of things.

@param  stringToErase, pointer to the string to erase

@return a new erase button handler object

*/
EraseButtonHandler::EraseButtonHandler(std::string* stringToErase)
{

    //set string to erase pointer to location input
    this->stringErase = stringToErase;

    //set both other pointers to null to indicate that we're not erasing those things
    this->vectorErase = NULL;
    this->intErase = NULL;
}

/**@brief Destructor for a button event handler
details This class does not dynamically allocate any objects, so the destructor is empty.

@param  none
@return none
*/
EraseButtonHandler::~EraseButtonHandler()
{

}


/**@brief Handles an event on the button that owns it
details This function takes a pointer to the event that happened on the owning button. If it is a button click event,
	the int/string/vector that was stored is deleted.

@param  event, pointer to an SDL event
@return none

*/
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