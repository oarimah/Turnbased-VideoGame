#ifndef ERASE_BUTTON_HANDLER_H
#define ERASE_BUTTON_HANDLER_H

#include "ButtonEventHandler.h"
#include "GameObject.h"
#include <vector>



class EraseButtonHandler : public ButtonEventHandler {

private:
	int* intErase;
	std::vector<GameObject*>* vectorErase;
	std::string* stringErase;


public:
	
	//erases int pointed to when button clicked
	EraseButtonHandler(int* intToErase);

	//erases vector pointed to when button clicked
	EraseButtonHandler(std::vector<GameObject*>* vectorToErase);

	//erases string pointed to when button clicked
	EraseButtonHandler(std::string* stringToErase);

	//destructor
	~EraseButtonHandler();

	void handleEvent(const SDL_Event* event);


};

#endif
