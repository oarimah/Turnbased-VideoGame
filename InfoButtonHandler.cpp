#include "InfoButtonHandler.h"

InfoButtonHandler::InfoButtonHandler(const std::string *displayText, TextDisplay* displayTo)
{
	this->text = displayText;
	this->displayBox = displayTo;

}

InfoButtonHandler::~InfoButtonHandler()
{
}

void InfoButtonHandler::handleEvent(const SDL_Event* event)
{

	//if button clicked, display the stored text to the given text display box
	if (event->type == SDL_MOUSEBUTTONUP) {

		this->displayBox->display(*this->text);
	}
}


