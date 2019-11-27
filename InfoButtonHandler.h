#ifndef INFO_BUTTON_HANDLER_H
#define INFO_BUTTON_HANDLER_H

#include "ButtonEventHandler.h"
#include "TextDisplay.h"



class InfoButtonHandler : public ButtonEventHandler {

private: 

	 const std::string* text;
	 TextDisplay* displayBox;

public:

	InfoButtonHandler(const std::string* displayText, TextDisplay* displayTo);
	~InfoButtonHandler();
	void handleEvent(const SDL_Event* event);
};

#endif 
