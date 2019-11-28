#include "InfoButtonHandler.h"

/**@brief Button event handler to change text display when button owning the handler is pushed
@author Carolyn Owen
details This class is owned by a button and provides functionality to display given text to the passed text display box when it is called
	
*/

/**@brief Constructor for a new info button handler object
details This function creates a new handler which stores a text string and reference to a display box. 
	When called, the stored text will be displayed to the display box.

@param  constant text string to print
@param 	pointer to text display box to print to 
@return	a new info button handler object
	
*/
InfoButtonHandler::InfoButtonHandler(const std::string *displayText, TextDisplay* displayTo)
{
	this->text = displayText;
	this->displayBox = displayTo;

}

/**@brief Destructor for info button handler objects
details This function safely deletes the info button handler. 
	Because there are no dynamically allocated objects stored only in the handler, the function is empty.

@param  none
@return none
*/
InfoButtonHandler::~InfoButtonHandler()
{
}

/**@brief Triggers event handling for info button, called when the button owning the handler is engaged
details This function takes a SDL event, checks that it is a valid click event and, if so, 
	displays the stored text in the display box that the handler points to.
@param  SDL event to handle
@return none
*/
void InfoButtonHandler::handleEvent(const SDL_Event* event)
{

	//if button clicked, display the stored text to the given text display box
	if (event->type == SDL_MOUSEBUTTONUP) {

		this->displayBox->display(*this->text);
	}
}


