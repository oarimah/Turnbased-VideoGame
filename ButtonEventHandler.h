#ifndef BUTTON_EVENT_HANDLER_H
#define BUTTON_EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include <string>

//abstract class to be used for concrete button event handlers with different behaviours


class ButtonEventHandler {

public: 

	virtual void handleEvent(const SDL_Event* event) = 0;
};

#endif
