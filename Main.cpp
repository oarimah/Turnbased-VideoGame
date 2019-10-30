#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Button.h"
#include "EraseButtonHandler.h"
#include "InfoButtonHandler.h"
#include "TextDisplay.h"



#undef main

int main() {


	const int TILE_WIDTH = 96;
	const int TILE_HEIGHT = 48;

	//initialize all systems for graphics handling

	//if can initialize SDL system, make a window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		//make a window show on the screen
		SDL_Window* window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 10 * TILE_WIDTH, (10 * TILE_HEIGHT + 100), SDL_WINDOW_SHOWN);

		//make renderer for the window using first available driver and no flags
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

		//make image handler for objects to use
		ImageHandler* imageHandler = new ImageHandler(renderer);

		//next try to initialize the text system for use with the text display box
		if (TTF_Init() == 0) {

			//create new text display box and locate it at bottom of map (make 2 tiles smaller in width to allow for continue button space under map)

			TextDisplay* displayBox = new TextDisplay("", 0, (10 * TILE_HEIGHT), 100, ((10 - 2) * TILE_WIDTH), renderer);
			displayBox->display("Text box displaying");


			//set up buttons with handlers and locations
			std::string continueString = "Continue button clicked.";
			ButtonEventHandler* continueHandler = new InfoButtonHandler(&continueString, displayBox);
			Button* continueButton = new Button(8 * TILE_WIDTH, 10 * TILE_HEIGHT, 100, 2 * TILE_WIDTH, continueHandler, "Continue.png", imageHandler);


			int i = 12;

			ButtonEventHandler* eraseHandler1 = new EraseButtonHandler(&i);

			Button* eraseButton1 = new Button(0 * TILE_WIDTH, 0 * TILE_HEIGHT, TILE_HEIGHT, TILE_WIDTH, eraseHandler1, "EraseButtonInt.png", imageHandler);


			std::string s = "I am a stored string";

			ButtonEventHandler* eraseHandler2 = new EraseButtonHandler(&s);

			Button* eraseButton2 = new Button(1 * TILE_WIDTH, 0 * TILE_HEIGHT, TILE_HEIGHT, TILE_WIDTH, eraseHandler2, "EraseButtonString.png", imageHandler);

			std::string info = "Info about button here";

			ButtonEventHandler* infoHandler = new InfoButtonHandler(&info, displayBox);

			Button* infoButton = new Button(2 * TILE_WIDTH, 0 * TILE_HEIGHT, TILE_HEIGHT, TILE_WIDTH, infoHandler, "InfoButton.png", imageHandler);

			std::string select = "Select button clicked.";
			ButtonEventHandler* selectHandler = new InfoButtonHandler(&select, displayBox);

			Button* selectButton = new Button(3 * TILE_WIDTH, 0 * TILE_HEIGHT, TILE_HEIGHT, TILE_WIDTH, selectHandler, "SelectButtonBefore.png", imageHandler);

			displayBox->display("Change display box text");


			bool notQuit = true;

			while (notQuit) {

				SDL_Event event;

				//if an event has happened, handle the event
				if (SDL_PollEvent(&event) == 1) {

					//if it is an event that should end the program, set bool value to break out of while loop
					if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
						notQuit = false;
					}


					else if (event.type == SDL_MOUSEBUTTONUP) {
						
						//show location of click
						std::cout << "event recognized at location " << std::endl;

						int x = event.button.x;
						int y = event.button.y;

						std::cout << "x= " << x << " y= " << y << std::endl;

						//if within top strip of buttons, check against x value to determine which button handles the event
						if (y < (1 * TILE_HEIGHT)) {

							//if in first column of tiles, check if at top or bottom
							if (x < TILE_WIDTH) {
								std::cout << "erase button before i = " << i << std::endl;
								eraseButton1->handleEvent(&event);
								std::cout << "erase button after i = " << i << std::endl;

							}

							else if ((x > 1 * TILE_WIDTH) && (x < 2 * TILE_WIDTH)) {
								std::cout << "erase button before s = " << s << std::endl;

								eraseButton2->handleEvent(&event);

								std::cout << "erase after before s = " << s << std::endl;
							}

							else if ((x > 2 * TILE_WIDTH) && (x < 3 * TILE_WIDTH)) {
								std::cout << "info button" << std::endl;
								infoButton->handleEvent(&event);
							}

							else if ((x > 3 * TILE_WIDTH) && (x < 4 * TILE_WIDTH)) {
								std::cout << "select button" << std::endl;
								selectButton->handleEvent(&event);
							}


						}

						//if at bottom and x value within continue button, pass event to continue button to handle
						else if (y > (10 * TILE_HEIGHT) && y < (10 * TILE_HEIGHT) + 100) {

							if ((x < 10 * TILE_WIDTH) && (x > 8 * TILE_WIDTH)) {
								std::cout << "continue button" << std::endl;
								continueButton->handleEvent(&event);
							}
						}

					}


					//clear renderer
					SDL_RenderClear(renderer);
					
					//render all objects
					continueButton->render();
					displayBox->render();
					eraseButton1->render();
					eraseButton2->render();
					infoButton->render();
					selectButton->render();
					
					//show rendering on window
					SDL_RenderPresent(renderer);


				}

			}

			//delete handlers
			delete infoHandler;
			delete selectHandler;
			delete continueHandler;
			delete eraseHandler1;
			delete eraseHandler2;

			//delete class objects
			delete imageHandler;
			delete displayBox;

			//delete buttons
			delete continueButton;
			delete eraseButton1;
			delete eraseButton2;
			delete infoButton;
			delete selectButton;


			//deinitialize systems
			TTF_Quit();
			SDL_Quit();

			//return from program 
			return 0;
		}

		//otherwise, print error and exit as other classes will fail without text display box
		else {

			std::cerr << "The SDL text system failed to initialize." << std::endl;

			//return unsuccessfully
			return -1;
		}


	}
	//otherwise, print a notification of failure and exit (can't go ahead without things initializing properly)
	else {
		std::cerr << "The SDL system failed to initialize." << std::endl;

		//return unsuccessfully
		return -1;

	}

}
