#include "Game.h"



Game::Game(int numTilesHigh, int numTilesWide, int tileWidth, int tileHeight) {

	//make height equal to the number of tiles times the tile height, plus 200 for the display text box at the bottom
	this->height = numTilesHigh;

	//set width equal to the number of tiles times the tile width
	this->width = numTilesWide;

	//set tile height and width
	this->tileHeight = tileHeight;
	this->tileWidth = tileWidth;

	//set image handler to null as not initialized  yet
	this->imageHandler = NULL;

	//create background and foreground maps


	//set running to false because init has not been called yet
	isRunning = false;

}



Game::~Game() {

	//if the game was initialized, erase the objects associated with it and deinit graphics
	if (this->isRunning) {
		//delete allocated objects

		delete this->imageHandler;
		delete this->displayBox;
		delete this->players[0];
		delete this->players[1];
		delete this->bgMap;
		//delete this->fgMap;

		//deinitialize systems
		TTF_Quit();
		SDL_Quit();
	}

	return;

}

int Game::init() {


	//initialize all systems for graphics handling

		//if can initialize SDL system, make a window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		//make a window show on the screen (add an extra strip of 100px to the window height to give space to text display box)
		SDL_Window* window = SDL_CreateWindow("Protect Your Territory", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width * this->tileWidth, (this->height * this->tileHeight + 100), SDL_WINDOW_SHOWN);

        std::cout << SDL_GetError() << std::endl;
		//make renderer for the window using first available driver and no flags
		this->renderer = SDL_CreateRenderer(window, -1, 0);

		//make image handler for objects to use
		ImageHandler* imageHandler = new ImageHandler(renderer);
		
		//set image handler in game object
		this->imageHandler = imageHandler;
        

		//next try to initialize the text system for use with the text display box
		if (TTF_Init() == 0) {

			//create new text display box and locate it at bottom of map (make 2 tiles smaller in width to allow for continue button space under map)

			TextDisplay* displayBox = new TextDisplay("", 0, (this->height * this->tileHeight), 100, ((this->width - (2 * this->width / 10)) * this->tileWidth), renderer);
			displayBox->display("Welcome! Let's play!");
			this->displayBox = displayBox;

			//create start screen that persists until the user clicks the continue button
			std::string continueString = "";
			ButtonEventHandler* continueHandler = new InfoButtonHandler(&continueString, displayBox);
			Button* continueButton = new Button(((this->width - (2 * this->width / 10)) * this->tileWidth), this->height * this->tileHeight, 100, ((2 * this->width / 10) * this->tileWidth), continueHandler, "button_continue.png", imageHandler);

			this->continueButton = continueButton;

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
			titlePos.x = (this->tileWidth * (0.2 * this->width));

			//locate title relative to the top of the screen
			titlePos.y = (this->tileHeight * (0.3 * this->height));

			//set the height relative to the height of the screen
			titlePos.h = ((0.4 * this->height) * this->tileHeight);

			//set the width relative to the width of the screen
			titlePos.w = ((0.6 * this->width) * this->tileWidth);

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
			while (SDL_WaitEvent(&event) && !continuePressed) {
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

				else if (event.type == SDL_MOUSEBUTTONUP) {
					//get the x location of the click
					int clickX = event.button.x;

					//if it's within the range of the continue button, check the y position
					if ((clickX < (this->width * this->tileWidth)) && (clickX > ((this->width - (2 * this->width / 10)) * this->tileWidth))) {

						int clickY = event.button.y;
						if ((clickY > (this->height * this->tileHeight) && clickY < (this->height * this->tileHeight) + 100)) {
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
			titlePos.x = (this->tileWidth * (0.2 * this->width));
			titlePos.y = (this->tileHeight * (0.1 * this->height));
			titlePos.h = ((0.2 * this->height) * this->tileHeight);
			titlePos.w = ((0.6 * this->width) * this->tileWidth);


			//set location for subtitle on window
			SDL_Rect subTitlePos;

			//set in line with the title
			subTitlePos.x = (this->tileWidth * (0.2 * this->width));

			//set below the title
			subTitlePos.y = (this->tileHeight * (0.4 * this->height));

			//set to be same size as title
			subTitlePos.h = ((0.1 * this->height) * this->tileHeight);
			subTitlePos.w = ((0.6 * this->height) * this->tileWidth);


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
			player1Pos.x = (this->tileWidth * (0.1 * this->width));

			//set below the subtitle
			player1Pos.y = (this->tileHeight * (0.6 * this->height));

			//set the height to be the same as the subtitle but the width to be less
			player1Pos.h = ((0.1 * this->height) * this->tileHeight);
			player1Pos.w = ((0.3 * this->height) * this->tileWidth);


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
			player2Pos.x = (this->tileWidth * (0.6 * this->width));

			//set below the subtitle
			player2Pos.y = (this->tileHeight * (0.6 * this->height));

			//set the height to be the same as the subtitle but the width to be 1/4 of it
			player2Pos.h = ((0.1 * this->height) * this->tileHeight);
			player2Pos.w = ((0.3 * this->height) * this->tileWidth);


			//create faction buttons to go below the player text

			//use the imageHandler to get the texture for both english and french factions (could not do for text as different steps involved)
			SDL_Texture* englishButton = imageHandler->loadImage("button_english.png");
			SDL_Texture* frenchButton = imageHandler->loadImage("button_french.png");

			//create rectangles and set positions of buttons underneath each player
			SDL_Rect player1English;

			//set below the player1 texts
			player1English.x = (this->tileWidth * (0.1 * this->width));
			player1English.y = (this->tileHeight * (0.8 * this->height));
			player1English.h = (this->tileHeight * (0.1 * this->height));
			player1English.w = (this->tileWidth * (0.1 * this->width));


			//create rectangle for player1 french button
			SDL_Rect player1French;

			player1French.x = (this->tileWidth * (0.3 * this->width));
			player1French.y = (this->tileHeight * (0.8 * this->height));
			player1French.h = (this->tileHeight * (0.1 * this->height));
			player1French.w = (this->tileWidth * (0.1 * this->width));


			//set player 2's buttons 
			SDL_Rect player2English;


			player2English.x = (this->tileWidth * (0.6 * this->width));
			player2English.y = (this->tileHeight * (0.8 * this->height));
			player2English.h = (this->tileHeight * (0.1 * this->height));
			player2English.w = (this->tileWidth * (0.1 * this->width));


			SDL_Rect player2French;


			player2French.x = (this->tileWidth * (0.8 * this->width));
			player2French.y = (this->tileHeight * (0.8 * this->height));
			player2French.h = (this->tileHeight * (0.1 * this->height));
			player2French.w = (this->tileWidth * (0.1 * this->width));



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
			while (SDL_WaitEvent(&event) && !continuePressed) {


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

				else if (event.type == SDL_MOUSEBUTTONUP) {
					//get the x location of the click
					int x = event.button.x;
					int y = event.button.y;

					//check to see if the continue button has been pressed, if so, set continuepressed to true to break while loop and proceed
					if ((x < (this->width * this->tileWidth)) && (x > ((this->width - (2 * this->width / 10)) * this->tileWidth))) {

						if ((y > (this->height * this->tileHeight) && y < (this->height * this->tileHeight) + 100)) {
							continuePressed = true;

						}
					}


					//otherwise, check the y value to see if it is within range of the faction buttons
					else if (y < ((0.9 * this->height) * this->tileHeight) && y >((0.8 * this->height) * this->tileHeight)) {

						//check x value to see what button has been pushed
						if (x < ((0.2 * this->width) * this->tileWidth) && x >((0.1 * this->width) * this->tileWidth)) {
							player1E = true;
						}

						else if (x < ((0.4 * this->width) * this->tileWidth) && x >((0.3 * this->width) * this->tileWidth)) {

							player1E = false;
						}

						else if (x < ((0.7 * this->width) * this->tileWidth) && x >((0.6 * this->width) * this->tileWidth)) {

							player2E = true;
						}

						else if (x < ((0.9 * this->width) * this->tileWidth) && x >((0.8 * this->width) * this->tileWidth)) {

							player2E = false;
						}
					}
				}

			}
			//delete no longer needed assets
			delete continueHandler;
			delete continueButton;
			
		//create the players using the above values for faction
        

        Player * player1;
        if (player1E){
			
            this->players[0] = new Player(1);
		}
        else{
            this->players[0]= new Player(2);
		}

        Player * player2;
        if (player2E){
            this->players[1] = new Player(1);
		}
        else{
            this->players[1] = new Player(2);
		}
        
		this->bgMap = new backgroundMap(this->tileHeight, this->tileWidth, this->width, this->height, this->imageHandler);
        this->fgMap = new foregroundMap(this->tileWidth, this->tileHeight, this->imageHandler, this->displayBox, this->players[0], this->players[1]);

		//otherwise, game is now running
		this->isRunning = true;
		
        //return successfully
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



void Game::eventHandler(const SDL_Event* event) {

	if (event->type == SDL_MOUSEBUTTONUP) {
		//get the x location of the click
		int x = event->button.x;
		int y = event->button.y;

		//check to see if the continue button has been pressed, if so, set player to next player and proceed
		if ((x < (this->width * this->tileWidth)) && (x > ((this->width - (2 * this->width / 10)) * this->tileWidth))) {

			if ((y > (this->height * this->tileHeight) && y < (this->height * this->tileHeight) + 100)) {
				this->currentPlayerIndex = (this->currentPlayerIndex + 1) % 2;

			}
		}

		//otherwise, make sure the click was in the map area before passing to the map to handl
		else if ((x < (this->width * this->tileWidth)) && (x > 0)) {

			if ((y < (this->height * this->tileHeight)) && (y > 0)) {

				this->fgMap->handleEvent(event, this->currentPlayerIndex);

			}


		}

	}
}

//render both layers of maps of the game
void Game::render() {

	//call render on all objects
	this->bgMap->render();
	this->fgMap->render();
	this->displayBox->render();
	
	this->continueButton->render();


}

void Game::renderClear(){
    SDL_RenderClear(this->renderer);
}

void Game::renderRepresent(){
    SDL_RenderPresent(this->renderer);
}

bool Game::running()
{
	return this->isRunning;
}


