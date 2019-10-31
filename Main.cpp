#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Button.h"
#include "Tile.h"
#include "EraseButtonHandler.h"
#include "InfoButtonHandler.h"
#include "TextDisplay.h"
//#include "backgroundMap.h"


#undef main

int main() {


	const int TILE_WIDTH = 32;
	const int TILE_HEIGHT = 16;

	//must be a multiple of 10
	const int NUM_TILES_WIDE = 20;
	const int NUM_TILES_HIGH = 20;

<<<<<<< HEAD
	//initialize all systems for graphics handling

	//if can initialize SDL system, make a window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		//make a window show on the screen (add an extra strip of 100px to the window height to give space to text display box)
		SDL_Window* window = SDL_CreateWindow("Protect Your Territory", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, NUM_TILES_WIDE * TILE_WIDTH, (NUM_TILES_HIGH * TILE_HEIGHT + 100), SDL_WINDOW_SHOWN);

		//make renderer for the window using first available driver and no flags
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

		//make image handler for objects to use
		ImageHandler* imageHandler = new ImageHandler(renderer);

		//next try to initialize the text system for use with the text display box
		if (TTF_Init() == 0) {

			//create new text display box and locate it at bottom of map (make 2 tiles smaller in width to allow for continue button space under map)

			TextDisplay* displayBox = new TextDisplay("", 0, (NUM_TILES_HIGH * TILE_HEIGHT), 100, ((NUM_TILES_WIDE - (2 * NUM_TILES_WIDE / 10)) * TILE_WIDTH), renderer);
			displayBox->display("Welcome! Let's play!");


			//create start screen that persists until the user clicks the continue button
			std::string continueString = "";
			ButtonEventHandler* continueHandler = new InfoButtonHandler(&continueString, displayBox);
			Button* continueButton = new Button(((NUM_TILES_WIDE - (2 * NUM_TILES_WIDE / 10)) * TILE_WIDTH), NUM_TILES_HIGH * TILE_HEIGHT, 100, ((2 * NUM_TILES_WIDE / 10) * TILE_WIDTH), continueHandler, "button_continue.png", imageHandler);

			//next section creates title for start screen
			
			//create font to use to display text
			TTF_Font* titleFont = TTF_OpenFont("Roboto-Bold.ttf", 48);

			//set color of the text
			SDL_Color titleColor = { 0,0,0 };
			
			//create surface from text, font and colour
			SDL_Surface* titleSurface;
			
			std::string titleString = "Protect Your Territory";
			titleSurface = TTF_RenderText_Solid(titleFont, titleString.c_str(), titleColor);

			//convert surface to texture and store 
			SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
			
			//set location for title on window
			SDL_Rect titlePos;
		
			//locate title relative to the left of the screen
			titlePos.x = (TILE_WIDTH * (0.2 * NUM_TILES_WIDE));
			
			//locate title relative to the top of the screen
			titlePos.y = (TILE_HEIGHT * (0.3 * NUM_TILES_HIGH));
			
			//set the height relative to the height of the screen
			titlePos.h = ((0.4 * NUM_TILES_HIGH) * TILE_HEIGHT);
			
			//set the width relative to the width of the screen
			titlePos.w = ((0.6 * NUM_TILES_WIDE) * TILE_WIDTH);
			
			//create background color
			SDL_Texture* background = imageHandler->loadImage("Background2Final.png");
						
			
			SDL_RenderClear(renderer);
			
			//render the text box and continue button
			imageHandler->render(background, NULL);
			
			displayBox->render();
			continueButton->render();
			
			//display the title to given title position
			SDL_RenderCopy(renderer, titleTexture, NULL, &titlePos);
			
			//present all to the screen
			SDL_RenderPresent(renderer);
			
			
			//set up event to store events from the window
			SDL_Event event;
			
			//set up bool to represent continue button being pressed
			bool continuePressed = false;
			
			
			//wait until there is an event and check it for the continue button being pressed or an end event
			while (SDL_WaitEvent(&event) && !continuePressed){
				//if it is an event that should end the program, set bool value to break out of while loop
				if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {

					//delete allocated objects
					delete continueButton;
					delete continueHandler;
					delete imageHandler;
					
					
					//deinitialize systems
					TTF_Quit();
					SDL_Quit();
					return 0;
				}
			
				else if (event.type == SDL_MOUSEBUTTONUP){
					//get the x location of the click
					int clickX = event.button.x;
					
					//if it's within the range of the continue button, check the y position
					if ((clickX <  (NUM_TILES_WIDE * TILE_WIDTH)) && (clickX > ((NUM_TILES_WIDE - (2 * NUM_TILES_WIDE / 10)) * TILE_WIDTH))){
						
						int clickY = event.button.y;
if ((clickY > (NUM_TILES_HIGH * TILE_HEIGHT) && clickY < (NUM_TILES_HIGH * TILE_HEIGHT) + 100)){
							continuePressed = true;
							
						}
					}
				}
		
			}
		//go to select factions page
		
			//create surface from text, font and colour for subtitle
			SDL_Surface* subTitleSurface;
			
			//use same font and color as title
			std::string subTitleString = "Select Your Factions";
			subTitleSurface = TTF_RenderText_Solid(titleFont, subTitleString.c_str(), titleColor);

			//convert surface to texture and store 
			SDL_Texture* subTitleTexture = SDL_CreateTextureFromSurface(renderer, subTitleSurface);

			
			//modify location for title on window (make smaller)
			titlePos.x = (TILE_WIDTH * (0.2 * NUM_TILES_WIDE));
			titlePos.y = (TILE_HEIGHT * (0.1 * NUM_TILES_HIGH));
			titlePos.h = ((0.2 * NUM_TILES_HIGH) * TILE_HEIGHT);
			titlePos.w = ((0.6 * NUM_TILES_WIDE) * TILE_WIDTH);
			

			//set location for subtitle on window
			SDL_Rect subTitlePos;
			
			//set in line with the title
			subTitlePos.x = (TILE_WIDTH * (0.2 * NUM_TILES_WIDE));
			
			//set below the title
			subTitlePos.y = (TILE_HEIGHT * (0.4 * NUM_TILES_HIGH));
			
			//set to be same size as title
			subTitlePos.h = ((0.1 * NUM_TILES_HIGH) * TILE_HEIGHT);
			subTitlePos.w = ((0.6 * NUM_TILES_HIGH) * TILE_WIDTH);
			
			
			//create font displays for Player 1 and Player 2
			//create surface from text, font and colour for player1
			SDL_Surface* player1Surface;
			
			//use same font and color as title
			std::string player1String = "Player 1";
			player1Surface = TTF_RenderText_Solid(titleFont, player1String.c_str(), titleColor);

			//convert surface to texture and store 
			SDL_Texture* player1Texture = SDL_CreateTextureFromSurface(renderer, player1Surface);
			
			//set location for player 1 text on window
			SDL_Rect player1Pos;
			
			//set in line with title/subtitle
			player1Pos.x = (TILE_WIDTH * (0.1 * NUM_TILES_WIDE));
			
			//set below the subtitle
			player1Pos.y = (TILE_HEIGHT * (0.6 * NUM_TILES_HIGH));
			
			//set the height to be the same as the subtitle but the width to be less
			player1Pos.h = ((0.1 * NUM_TILES_HIGH) * TILE_HEIGHT);
			player1Pos.w = ((0.3 * NUM_TILES_HIGH) * TILE_WIDTH);
			
			
			//create surface from text, font and colour for player2
			SDL_Surface* player2Surface;
			
			//use same font and color as title
			std::string player2String = "Player 2";
			player2Surface = TTF_RenderText_Solid(titleFont, player2String.c_str(), titleColor);

			//convert surface to texture and store 
			SDL_Texture* player2Texture = SDL_CreateTextureFromSurface(renderer, player2Surface);
			
			//set location for player 2 text on window
			SDL_Rect player2Pos;
			
			//set in line right end of subtitle/title
			player2Pos.x = (TILE_WIDTH * (0.6 * NUM_TILES_WIDE));
			
			//set below the subtitle
			player2Pos.y = (TILE_HEIGHT * (0.6 * NUM_TILES_HIGH));
			
			//set the height to be the same as the subtitle but the width to be 1/4 of it
			player2Pos.h = ((0.1 * NUM_TILES_HIGH) * TILE_HEIGHT);
			player2Pos.w = ((0.3 * NUM_TILES_HIGH) * TILE_WIDTH);
			
			
			//create faction buttons to go below the player text
			
			//use the imageHandler to get the texture for both english and french factions (could not do for text as different steps involved)
			SDL_Texture* englishButton = imageHandler->loadImage("button_english.png");
			SDL_Texture* frenchButton = imageHandler->loadImage("button_french.png");
			
			//create rectangles and set positions of buttons underneath each player
			SDL_Rect player1English;
			
			//set below the player1 texts
			player1English.x = (TILE_WIDTH * (0.1 * NUM_TILES_WIDE));
			player1English.y = (TILE_HEIGHT * (0.8 * NUM_TILES_HIGH));
			player1English.h = (TILE_HEIGHT * (0.1 * NUM_TILES_HIGH));
			player1English.w = (TILE_WIDTH * (0.1 * NUM_TILES_WIDE));
			
			
			//create rectangle for player1 french button
			SDL_Rect player1French;
			
			player1French.x = (TILE_WIDTH * (0.3 * NUM_TILES_WIDE));
			player1French.y = (TILE_HEIGHT * (0.8 * NUM_TILES_HIGH));
			player1French.h = (TILE_HEIGHT * (0.1 * NUM_TILES_HIGH));
			player1French.w = (TILE_WIDTH * (0.1 * NUM_TILES_WIDE));
			
			
			//set player 2's buttons 
			SDL_Rect player2English;
			
			
			player2English.x = (TILE_WIDTH * (0.6 * NUM_TILES_WIDE));
			player2English.y = (TILE_HEIGHT * (0.8 * NUM_TILES_HIGH));
			player2English.h = (TILE_HEIGHT * (0.1 * NUM_TILES_HIGH));
			player2English.w = (TILE_WIDTH * (0.1 * NUM_TILES_WIDE));
			
			
			SDL_Rect player2French;
			
			
			player2French.x = (TILE_WIDTH * (0.8 * NUM_TILES_WIDE));
			player2French.y = (TILE_HEIGHT * (0.8 * NUM_TILES_HIGH));
			player2French.h = (TILE_HEIGHT * (0.1 * NUM_TILES_HIGH));
			player2French.w = (TILE_WIDTH * (0.1 * NUM_TILES_WIDE));
		
			
						
			//render background colour, text display box, continue button, title			
			SDL_RenderClear(renderer);
			
			//render the background 
			SDL_RenderCopy(renderer, background, NULL, NULL);
			
			//render the text box and continue button
			displayBox->render();
			continueButton->render();
			
			//display the title to given title position
			SDL_RenderCopy(renderer, titleTexture, NULL, &titlePos);
			
			//display the subtitle to given position
			SDL_RenderCopy(renderer, subTitleTexture, NULL, &subTitlePos);
			
			//display player1 and player2 text to given position
			SDL_RenderCopy(renderer, player1Texture, NULL, &player1Pos);
			SDL_RenderCopy(renderer, player2Texture, NULL, &player2Pos);
			
			
			//display player1's buttons and player2's buttons, using the same english and french buttons in their respective positions for each player
			SDL_RenderCopy(renderer, englishButton, NULL, &player1English);
			SDL_RenderCopy(renderer, frenchButton, NULL, &player1French);
			SDL_RenderCopy(renderer, englishButton, NULL, &player2English);
			SDL_RenderCopy(renderer, frenchButton, NULL, &player2French);
			
			
			//present all to the screen
			SDL_RenderPresent(renderer);
			
			//set up tracker for factions of each player
			//defaults to english for each player, if button for french pressed, the tracker will switch, and will switch back if english then pressed
			bool player1E = true;
			bool player2E = true;
			
			
			//reset bool to represent continue button being pressed, which will continue the game initialization
			continuePressed = false;
			
			//wait until there is an event and check it for the continue button being pressed
			while (SDL_WaitEvent(&event) && !continuePressed){
		
				
				//if it is an event that should end the program, set bool value to break out of while loop
				if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
					
					//delete allocated objects
					delete continueButton;
					delete continueHandler;
					delete imageHandler;
					
					
					//deinitialize systems
					TTF_Quit();
					SDL_Quit();
					return 0;
				}
			
				else if (event.type == SDL_MOUSEBUTTONUP){
					//get the x location of the click
					int x = event.button.x;
					int y = event.button.y;
					
					//check to see if the continue button has been pressed, if so, set continuepressed to true to break while loop and proceed
					if ((x <  (NUM_TILES_WIDE * TILE_WIDTH)) && (x > ((NUM_TILES_WIDE - (2 * NUM_TILES_WIDE / 10)) * TILE_WIDTH))){
						
						if ((y > (NUM_TILES_HIGH * TILE_HEIGHT) && y < (NUM_TILES_HIGH * TILE_HEIGHT) + 100)){
							continuePressed = true;
							
						}
					}
					
					
					//otherwise, check the y value to see if it is within range of the faction buttons
					else if (y < ((0.9 * NUM_TILES_HIGH ) * TILE_HEIGHT) && y > ((0.8 * NUM_TILES_HIGH) * TILE_HEIGHT)){
						
						//check x value to see what button has been pushed
						if (x < ((0.2 * NUM_TILES_WIDE) * TILE_WIDTH) && x > ((0.1 * NUM_TILES_WIDE) * TILE_WIDTH)){
							player1E = true;
						} 
						
						else if (x < ((0.4 * NUM_TILES_WIDE) * TILE_WIDTH) && x > ((0.3 * NUM_TILES_WIDE) * TILE_WIDTH)){
							
							player1E = false;
						}
						
						else if (x < ((0.7 * NUM_TILES_WIDE) * TILE_WIDTH) && x > ((0.6 * NUM_TILES_WIDE) * TILE_WIDTH)){
							
							player2E = true;
						}
						
						else if (x < ((0.9 * NUM_TILES_WIDE) * TILE_WIDTH) && x > ((0.8 * NUM_TILES_WIDE) * TILE_WIDTH)){
							
							player2E = false;
						}
					}		
				}
			
			}
			//create the players using the above values for faction
			
			//PUT GAMELOOP HERE
			
			
			
			std::cout<<"IN GAME LOOP"<<std::endl;
			
			//delete allocated objects
			delete continueButton;
			delete continueHandler;
			delete imageHandler;
			//delete tile;

			//deinitialize systems
			TTF_Quit();
			SDL_Quit();
			return 0;
		 
			
			

			/*	
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

            Tile* tile = new Tile(TILE_WIDTH, TILE_HEIGHT, 150, 150, "testTile.png", imageHandler);
=======
	//set frame rate and frame delay
	const int FRAME_RATE = 60;
	const int FRAME_DELAY = 1000 / FRAME_RATE;
>>>>>>> 824d47e79abda95b61fde5a00f683d3bc57a4d78


	//create a new game
	Game* game = new Game(NUM_TILES_HIGH, NUM_TILES_WIDE, TILE_WIDTH, TILE_HEIGHT);

	//initialize the game
	int success = game.init();

	//declare storage for time that frame was first displayed and the time that the frame has been up
	uint_32 firstDisplayed;
	int frameTime;


	//if game init returns 0, it was successful, otherwise it didn't work
	if (success == 0) {

		//start the game loop

		while (game.running()) {

			//initialize the first displayed time of the frame
			firstDisplayed = SDL_GetTicks();

			//try to get an event
			//set up event to store events from the window
			SDL_Event event;

			//wait until there is an event and check it for an end event
			if (SDL_WaitEvent(&event)) {
				//if it is an event that should end the program, set bool value to break out of while loop
				if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {

					//delete allocated objects and return
					delete game;
					return 0;
				}

				//otherwise, send the event to the game to handle
				else {
					this->game->handleEvent(&event);
				}


			}

			//render everything
			//clear renderer
			SDL_RenderClear(this->renderer);

			//call render on game to display everything
			game->render();

			//update the window with the newly rendered image above
			SDL_RenderPresent(this->renderer);


			//calculate the time that the frame has been displayed
			frameTime = SDL_GetTicks() - firstDisplayed;

			//if the frame has been displayed less time than the required delay, delay the frame
			if (frameTime > FRAME_DELAY) {

				//delay by the difference between the required delay and the time it's been up so far
				SDL_Delay(FRAME_DELAY - frameTime);
			}

		}

		//game no longer running delete the game and return from main
		delete this->game;
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
	






