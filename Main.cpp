#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Button.h"
#include "Game.h"
#include "EraseButtonHandler.h"
#include "InfoButtonHandler.h"
#include "TextDisplay.h"

#undef main

int main() {

	const int TILE_WIDTH = 25;
	const int TILE_HEIGHT = 25;

	//must be a multiple of 10
	const int NUM_TILES_WIDE = 20;
	const int NUM_TILES_HIGH = 20;

	//set frame rate and frame delay
	const int FRAME_RATE = 60;
	const int FRAME_DELAY = 1000 / FRAME_RATE;
	//initialize all systems for graphics handling

	Game * game = new Game(NUM_TILES_HIGH, NUM_TILES_WIDE, TILE_WIDTH,
			TILE_HEIGHT);
	//if can initialize SDL system, make a window and renderer

	//initialize the game
	int success = game->init();

	//declare storage for time that frame was first displayed and the time that the frame has been up
	unsigned long int firstDisplayed;
	int frameTime;

	//if game init returns 0, it was successful, otherwise it didn't work
	if (success == 0) {

		std::cout << "entered game loop" << std::endl;

		//start the game loop
		while (game->running()) {

			//render everything
			//clear renderer
			game->renderClear();

			//call render on game to display everything
			game->render();

			//update the window with the newly rendered image above
			game->renderRepresent();

			//initialize the first displayed time of the frame
			firstDisplayed = SDL_GetTicks();

			//try to get an event
			//set up event to store events from the window
			SDL_Event event;

			//calculate the time that the frame has been displayed
			frameTime = SDL_GetTicks() - firstDisplayed;

			//if the frame has been displayed less time than the required delay, delay the frame
			if (frameTime > FRAME_DELAY) {

				//delay by the difference between the required delay and the time it's been up so far
				SDL_Delay(FRAME_DELAY - frameTime);
			}

			//wait until there is an event and check it for an end event
			while (SDL_WaitEvent(&event)) {
				//if it is an event that should end the program, set bool value to break out of while loop
				if (event.type == SDL_QUIT
						|| event.type == SDL_WINDOWEVENT_CLOSE) {

					//delete allocated objects and return
					delete game;
					return 0;
				}

				//otherwise, send the event to the game to handle
				else {

					game->eventHandler(&event);
				}

			}

		}

		//game no longer running delete the game and return from main
		delete game;
		return 0;
	}

	else {

		//print notification to the user and exit the program
		std::cout << "The game could not be started, sorry!" << std::endl;

		//delete the game object
		delete game;

		//return unsuccessfully

	}
}

