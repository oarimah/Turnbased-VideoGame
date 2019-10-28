/*#ifndef SELECT_BUTTON_HANDLER_H
#define SELECT_BUTTON_HANDLER_H

#include "SDL.h"
#include "SDL_image.h"
#include "ButtonEventHandler.h"



class SelectButtonHandler : public ButtonEventHandler {

private:

	std::string changeImageFile;

public:

	SelectButtonHandler(const std::string& changeImageToFile);
	~SelectButtonHandler();
	void handleEvent(const SDL_Event* event);

};

#endif*/