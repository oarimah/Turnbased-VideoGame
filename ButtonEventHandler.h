#ifndef BUTTON_EVENT_HANDLER_H
#define BUTTON_EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include <string>

/**@brief Template to require functions to be defined by all button event handler subclasses
@author
details This class requires all button event handlers to have a handle event method that takes an SDL event

*/

class ButtonEventHandler {

public: 

	virtual void handleEvent(const SDL_Event* event) = 0;
};

#endif
