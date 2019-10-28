#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Button.h"
#include "ContinueHandler.h"
#include "EraseButtonHandler.h"
#include "InfoButtonHandler.h"
#include "SelectButtonHandler.h"
#include "TextDisplay.h"



#undef main

int main() {



	const int TILE_WIDTH = 32;
	const int TILE_HEIGHT = 32;

	//initialize all systems for graphics handling

	//if can initialize SDL system, make a window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		SDL_Window* window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 10 * TILE_WIDTH, (10 * TILE_HEIGHT + 200), SDL_WINDOW_SHOWN);

		//make renderer for the window using first available driver and no flags
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

		ImageHandler* imageHandler = new ImageHandler(renderer);

		//next try to initialize the text system for use with the text display box
		if (TTF_Init() == 0) {

			//create new text display box and locate it at bottom of map (make 2 tiles smaller in width to allow for continue button space under map)

			TextDisplay* displayBox = new TextDisplay("", 0, (10 * TILE_HEIGHT), 200, ((10 - 2) * TILE_WIDTH), renderer);
			displayBox->display("Text box displaying");

			std::string continueString = "Continue button clicked.";
			ButtonEventHandler* continueHandler = new InfoButtonHandler(&continueString, displayBox);
			Button* continueButton = new Button(8 * TILE_WIDTH, 10 * TILE_HEIGHT, 200, 2 * TILE_WIDTH, continueHandler, "Continue.png", imageHandler);


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




			while (true) {
				SDL_Event event;

				if (SDL_PollEvent(&event) == 1) {

					if (event.type == SDL_MOUSEBUTTONUP) {

						int x = event.button.x;
						int y = event.button.y;

						if (y > (9 * TILE_HEIGHT) + 200) {

							//if in first column of tiles, check if at top or bottom
							if (x < TILE_WIDTH) {

								eraseButton1->handleEvent(&event);

							}

							else if ((x > 1 * TILE_WIDTH) && (x < 2 * TILE_WIDTH)) {

								eraseButton2->handleEvent(&event);
							}

							else if ((x > 2 * TILE_WIDTH) && (x < 3 * TILE_WIDTH)) {

								infoButton->handleEvent(&event);
							}

							else if ((x > 3 * TILE_WIDTH) && (x < 4 * TILE_WIDTH)) {
								selectButton->handleEvent(&event);
							}


						}

						else if (y < 200) {

							if ((x < 10 * TILE_WIDTH) && (x > 8 * TILE_WIDTH)) {

								continueButton->handleEvent(&event);
							}
						}

					}
				}

				std::cout << "i = " << i << std::endl;

				std::cout << "String s = " << s << std::endl;

				SDL_RenderClear(renderer);
				continueButton->render();
				displayBox->render();
				eraseButton1->render();
				eraseButton2->render();
				infoButton->render();
				selectButton->render();
				SDL_RenderPresent(renderer);


			}

		}

		//otherwise, print error and exit as other classes will fail without text display box
		else {

		std::cerr << "The SDL text system failed to initialize." << std::endl;
		}
	}


	//otherwise, print a notification of failure and exit (can't go ahead without things initializing properly)
	else {
	std::cerr << "The SDL system failed to initialize." << std::endl;
	}
	
}

