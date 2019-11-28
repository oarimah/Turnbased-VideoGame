#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Button.h"
#include "Game.h"
#include "EraseButtonHandler.h"
#include "InfoButtonHandler.h"
#include "TextDisplay.h"

#undef main

/**@brief Main controls creation and management of game object
@author Carolyn Owen
details This class defines the size of the game window and creates a new game object. While the game is running, 
	main renders the game to the window, gets an event indicating interaction with the game window, 
	checks to make sure that it isn't an end event and passes it to the game to handle. If the game ends or the 
	player triggers an end event in the window, main gracefully exits from the program, deleting all objects as required (in all levels)

*/
int main() {

	const int TILE_WIDTH = 32;
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
			while (true)
				
				if(SDL_PollEvent(&event))
					if (event.type != SDL_MOUSEMOTION && event.type != SDL_MOUSEBUTTONDOWN){
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
				break;
			

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

