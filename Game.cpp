#include "Game.h"



/**@brief Game class defines and manages all assets and events involved in playing the game
@author Carolyn Owen
@author Abdallah Alasmar
@author Oluwadarasimi Ogunshote
details This class creates a new game window, maps, players, units, buttons, displays for the game. 
	It takes events from the main class and delegates them appropriately based on type and location. 
	
*/



/**@brief Constructor for a new game object
details This function takes size of tiles and number of tiles high and wide for the game to be created. 
	These parameters are saved for future use. Member variables for current player, game status and image handler are set to initial values 
	(nothing initialized here, all of that is done in the init function).

@param 	int number of tiles high
@param 	int number of tiles wide
@param 	int width of the individual tiles in pixels
@param 	int height of the individual tiles in pixels

@return a new game object
	
*/
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

	// set the player to start the game
	this->currentPlayerIndex = 1;

	//create background and foreground maps

	//set running to false because init has not been called yet
	isRunning = false;

}



/**@brief Destructor for a game object
details If the game has been initialized, this function deallocates memory set aside for the image handler, 
	display box, players, and maps. Then it deinitializes the SDL and text display systems

@param  none
@return none
	
*/
Game::~Game() {

	//if the game was initialized, erase the objects associated with it and deinit graphics
	if (this->isRunning) {
		//delete allocated objects

		delete this->imageHandler;
		delete this->displayBox;
		delete this->players[0];
		delete this->players[1];
		delete this->bgMap;
		delete this->fgMap;

		//deinitialize systems
		TTF_Quit();
		SDL_Quit();
	}

	return;

}



/**@brief Initializer for game object to be called after object creation.
details This function executes many steps to display the game and set up the game parameters through a graphical interface to the players.
	The steps that the game initializer takes are below:
	
	- try to initialize SDL graphics handling systems
	- if not successful, print an error and exit the program
	- else create a new window, renderer and image handler for the game and do the below
	- try to intialize the SDL text to image handling systems
	- if not successful, print an error and exit the program
	- else create a text display box for the game and do the below
	- create a continue button to be used throughout the game
	- create title screen with game name, background and button to get the rules
	- when clicked, the rules button brings the player to a display with the rules until they 
		press the continue button, when it returns to the title screen
	- when continue button clicked from the title page, display a page with the player numbers and buttons to select the players' factions
	- when continue button clicked from the factions page, the players will be created and added to the game object with the selected 
		factions, or english factions as default
	- create a new button to end the player's turn and replace continue button with it
	- create control points and add them to the game object
	- create background and foreground maps for the game object
	- set the game running to true as all things have happened to allow the game to be played. 

@param  none
@return int representing success (0) or failure (-1) to initialize
	

*/
int Game::init() {

	//initialize all systems for graphics handling

	//if can initialize SDL system, make a window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		//make a window show on the screen (add an extra strip of 200px to the window height to give space to text display box)
		SDL_Window* window = SDL_CreateWindow("Protect Your Territory",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			(this->width * this->tileWidth) + 200,
			(this->height * this->tileHeight), SDL_WINDOW_SHOWN);

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

			TextDisplay* displayBox = new TextDisplay("", (this->tileWidth * this->width),
				0, ((this->height - 2) * this->tileHeight), 200, renderer);
			this->displayBox = displayBox;

			//create start screen that persists until the user clicks the continue button
			std::string continueString = "";
			ButtonEventHandler* continueHandler = new InfoButtonHandler(
				&continueString, displayBox);
			Button* continueButton = new Button(
				(this->tileWidth * this->width),
				((this->height - 2) * this->tileHeight), (this->tileHeight * 2), 200
				, continueHandler,
				"Buttons/Continue.png", imageHandler);

			this->continueButton = continueButton;

			//make a button that will open a rules window when pushed

			SDL_Texture* ruleButton = imageHandler->loadImage(
				"Buttons/Rules.png");

			//create rectangles and set positions of buttons underneath each player
			SDL_Rect rulesPos;

			//set below the player1 texts
			rulesPos.x = 300;
			rulesPos.y = 350;
			rulesPos.h = 50;
			rulesPos.w = 100;


			//next section creates title for start screen

			//create font to use to display text
			TTF_Font* titleFont = TTF_OpenFont("Fonts/CaviarDreams_Bold.ttf", 72);

			//set color of the text
			SDL_Color titleColor = { 0, 0, 0 };

			//create surface from text, font and colour
			SDL_Surface* titleSurface;

			std::string titleString = "Protect Your Territory";
			titleSurface = TTF_RenderText_Solid(titleFont, titleString.c_str(),
				titleColor);

			//convert surface to texture and store
			SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer,
				titleSurface);

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
			SDL_Texture* background = imageHandler->loadImage(
				"Background/Background2Final.png");

			SDL_RenderClear(renderer);

			//render the text box, rule button and continue button
			imageHandler->render(background, NULL);

			SDL_RenderCopy(renderer, ruleButton, NULL, &rulesPos);
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
			while (!continuePressed && SDL_WaitEvent(&event)) {
				//if it is an event that should end the program, set bool value to break out of while loop
				if (event.type == SDL_QUIT
					|| event.type == SDL_WINDOWEVENT_CLOSE) {

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
					if ((clickX < ((this->width * this->tileWidth) + 200))
						&& (clickX
					> (this->width * this->tileWidth))) {

						int clickY = event.button.y;
						if (clickY > ((this->height - 2) * this->tileHeight)
							&& clickY
							< (this->height * this->tileHeight)) {
							continuePressed = true;

						}
					}

					//if it's within the range of the rule button, check the y position before calling the handler
					if ((clickX < 400)
						&& (clickX > 300)) {

						int clickY = event.button.y;
						if (clickY > 350 && clickY < 400) {
							
							//call function to display the rules screen
							rules();

							//re-display the title screen
							SDL_RenderClear(renderer);
				
							//render the text box, rule button and continue button
							imageHandler->render(background, NULL);
				
							SDL_RenderCopy(renderer, ruleButton, NULL, &rulesPos);
							displayBox->render();
							continueButton->render();
				
							//display the title to given title position
							SDL_RenderCopy(renderer, titleTexture, NULL, &titlePos);
				
							//present all to the screen
							SDL_RenderPresent(renderer);

						}
					}
				}
			}
			//go to select factions page

			//create surface from text, font and colour for subtitle
			SDL_Surface* subTitleSurface;

			//use same font and color as title
			std::string subTitleString = "Select Your Factions";
			subTitleSurface = TTF_RenderText_Solid(titleFont,
				subTitleString.c_str(), titleColor);

			//convert surface to texture and store
			SDL_Texture* subTitleTexture = SDL_CreateTextureFromSurface(
				renderer, subTitleSurface);

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
			player1Surface = TTF_RenderText_Solid(titleFont,
				player1String.c_str(), titleColor);

			//convert surface to texture and store
			SDL_Texture* player1Texture = SDL_CreateTextureFromSurface(renderer,
				player1Surface);

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
			player2Surface = TTF_RenderText_Solid(titleFont,
				player2String.c_str(), titleColor);

			//convert surface to texture and store
			SDL_Texture* player2Texture = SDL_CreateTextureFromSurface(renderer,
				player2Surface);

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
			SDL_Texture* englishButton = imageHandler->loadImage(
				"Buttons/English.png");
			SDL_Texture* frenchButton = imageHandler->loadImage(
				"Buttons/French.png");
			SDL_Texture* germanButton = imageHandler->loadImage(
				"Buttons/German.png");
			SDL_Texture* spanishButton = imageHandler->loadImage(
				"Buttons/Spanish.png");

			//create rectangles and set positions of buttons underneath each player
			SDL_Rect player1English;

			//set below the player1 texts
			player1English.x = (this->tileWidth * (0.0 * this->width));
			player1English.y = (this->tileHeight * (0.8 * this->height));
			player1English.h = (this->tileHeight * (0.1 * this->height));
			player1English.w = (this->tileWidth * (0.1 * this->width));

			//create rectangle for player1 french button
			SDL_Rect player1French;

			player1French.x = (this->tileWidth * (0.1 * this->width));
			player1French.y = (this->tileHeight * (0.8 * this->height));
			player1French.h = (this->tileHeight * (0.1 * this->height));
			player1French.w = (this->tileWidth * (0.1 * this->width));

			//create rectangle for player1 german button
			SDL_Rect player1German;

			player1German.x = (this->tileWidth * (0.2 * this->width));
                        player1German.y = (this->tileHeight * (0.8 * this->height));
                        player1German.h = (this->tileHeight * (0.1 * this->height));
                        player1German.w = (this->tileWidth * (0.1 * this->width));

			//create rectangle for player1 spanish button
			SDL_Rect player1Spanish;

			player1Spanish.x = (this->tileWidth * (0.3 * this->width));
                        player1Spanish.y = (this->tileHeight * (0.8 * this->height));
                        player1Spanish.h = (this->tileHeight * (0.1 * this->height));
                        player1Spanish.w = (this->tileWidth * (0.1 * this->width));

			//set player 2's buttons
			SDL_Rect player2English;

			player2English.x = (this->tileWidth * (0.5 * this->width));
			player2English.y = (this->tileHeight * (0.8 * this->height));
			player2English.h = (this->tileHeight * (0.1 * this->height));
			player2English.w = (this->tileWidth * (0.1 * this->width));

			SDL_Rect player2French;

			player2French.x = (this->tileWidth * (0.6 * this->width));
			player2French.y = (this->tileHeight * (0.8 * this->height));
			player2French.h = (this->tileHeight * (0.1 * this->height));
			player2French.w = (this->tileWidth * (0.1 * this->width));

			SDL_Rect player2German;

			player2German.x = (this->tileWidth * (0.7 * this->width));
                        player2German.y = (this->tileHeight * (0.8 * this->height));
                        player2German.h = (this->tileHeight * (0.1 * this->height));
                        player2German.w = (this->tileWidth * (0.1 * this->width));

			SDL_Rect player2Spanish;

			player2Spanish.x = (this->tileWidth * (0.8 * this->width));
                        player2Spanish.y = (this->tileHeight * (0.8 * this->height));
                        player2Spanish.h = (this->tileHeight * (0.1 * this->height));
                        player2Spanish.w = (this->tileWidth * (0.1 * this->width));

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
			SDL_RenderCopy(renderer, germanButton, NULL, &player1German);
			SDL_RenderCopy(renderer, spanishButton, NULL, &player1Spanish);
			SDL_RenderCopy(renderer, englishButton, NULL, &player2English);
			SDL_RenderCopy(renderer, frenchButton, NULL, &player2French);
			SDL_RenderCopy(renderer, germanButton, NULL, &player2German);
			SDL_RenderCopy(renderer, spanishButton, NULL, &player2Spanish);

			//present all to the screen
			SDL_RenderPresent(renderer);

			//set up tracker for factions of each player
			//defaults to english for each player, if button for a different faction is pressed, the tracker will switch, and will switch back if english is then pressed
			bool player1E = true;
			bool player1F = false;
			bool player1G = false;
			bool player1S = false;
			bool player2E = true;
			bool player2F = false;
			bool player2G = false;
			bool player2S = false;

			//reset bool to represent continue button being pressed, which will continue the game initialization
			continuePressed = false;

			//wait until there is an event and check it for the continue button being pressed
			while (!continuePressed && SDL_WaitEvent(&event)) {

				//if it is an event that should end the program, set bool value to break out of while loop
				if (event.type == SDL_QUIT
					|| event.type == SDL_WINDOWEVENT_CLOSE) {

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
					if ((x < ((this->width * this->tileWidth) + 200))
						&& (x
					> (this->width * this->tileWidth))) {

						if ((y > ((this->height - 2) * this->tileHeight))
							&& y < (this->height * this->tileHeight)) {
							continuePressed = true;

						}
					}



					//otherwise, check the y value to see if it is within range of the faction buttons
					if (y < ((0.9 * this->height) * this->tileHeight)
						&& y >((0.8 * this->height) * this->tileHeight)) {

						//check x value to see what button has been pushed
						if (x < ((0.1 * this->width) * this->tileWidth)
							&& x
						>((0.0 * this->width) * this->tileWidth)) {
							player1E = true;
							player1F = false;
							player1G = false;
							player1S = false;

							//display this choice to the screen
							this->displayBox->display("Player 1:\nEnglish");

							//re-render background colour, text display box, continue button
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

							//display player1's buttons and player2's buttons, using the same english, french, german, and spanish buttons in their respective positions for each player
							SDL_RenderCopy(renderer, englishButton, NULL, &player1English);
                       	 				SDL_RenderCopy(renderer, frenchButton, NULL, &player1French);
                        				SDL_RenderCopy(renderer, germanButton, NULL, &player1German);
                        				SDL_RenderCopy(renderer, spanishButton, NULL, &player1Spanish);
                        				SDL_RenderCopy(renderer, englishButton, NULL, &player2English);
                        				SDL_RenderCopy(renderer, frenchButton, NULL, &player2French);
                        				SDL_RenderCopy(renderer, germanButton, NULL, &player2German);
                        				SDL_RenderCopy(renderer, spanishButton, NULL, &player2Spanish);

							//present all to the screen
							SDL_RenderPresent(renderer);

						}

						else if (x < ((0.2 * this->width) * this->tileWidth)
							&& x
						>((0.1 * this->width) * this->tileWidth)) {

							player1E = false;
							player1F = true;
							player1G = false;
							player1S = false;

							//display this choice to the screen
							this->displayBox->display("Player 1:\nFrench");

							//re-render background colour, text display box, continue button
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
                        				SDL_RenderCopy(renderer, germanButton, NULL, &player1German);
                       					SDL_RenderCopy(renderer, spanishButton, NULL, &player1Spanish);
                      					SDL_RenderCopy(renderer, englishButton, NULL, &player2English);
                        				SDL_RenderCopy(renderer, frenchButton, NULL, &player2French);
                        				SDL_RenderCopy(renderer, germanButton, NULL, &player2German);
				                        SDL_RenderCopy(renderer, spanishButton, NULL, &player2Spanish);


							//present all to the screen
							SDL_RenderPresent(renderer);

						}

						else if (x < ((0.3 * this->width) * this->tileWidth)
                                                        && x
                                                >((0.2 * this->width) * this->tileWidth)) {

                                                        player1E = false;
							player1F = false;
							player1G = true;
							player1S = false;

                                                        //display this choice to the screen
                                                        this->displayBox->display("Player 1:\nGermans");

                                                        //re-render background colour, text display box, continue button
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
                                                        SDL_RenderCopy(renderer, germanButton, NULL, &player1German);
                                                        SDL_RenderCopy(renderer, spanishButton, NULL, &player1Spanish);
                                                        SDL_RenderCopy(renderer, englishButton, NULL, &player2English);
                                                        SDL_RenderCopy(renderer, frenchButton, NULL, &player2French);
                                                        SDL_RenderCopy(renderer, germanButton, NULL, &player2German);
                                                        SDL_RenderCopy(renderer, spanishButton, NULL, &player2Spanish);


                                                        //present all to the screen
                                                        SDL_RenderPresent(renderer);

                                                }

						else if (x < ((0.4 * this->width) * this->tileWidth)
                                                        && x
                                                >((0.3 * this->width) * this->tileWidth)) {

                                                        player1E = false;
							player1F = false;
							player1G = false;
							player1S = true;

                                                        //display this choice to the screen
                                                        this->displayBox->display("Player 1:\nSpanish");

                                                        //re-render background colour, text display box, continue button
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
                                                        SDL_RenderCopy(renderer, germanButton, NULL, &player1German);
                                                        SDL_RenderCopy(renderer, spanishButton, NULL, &player1Spanish);
                                                        SDL_RenderCopy(renderer, englishButton, NULL, &player2English);
                                                        SDL_RenderCopy(renderer, frenchButton, NULL, &player2French);
                                                        SDL_RenderCopy(renderer, germanButton, NULL, &player2German);
                                                        SDL_RenderCopy(renderer, spanishButton, NULL, &player2Spanish);


                                                        //present all to the screen
                                                        SDL_RenderPresent(renderer);

                                                }


						else if (x < ((0.6 * this->width) * this->tileWidth)
							&& x
						>((0.5 * this->width) * this->tileWidth)) {

							player2E = true;
							player2F = false;
							player2G = false;
							player2S = false;

							//display this choice to the screen
							this->displayBox->display("Player 2:\nEnglish");

							//re-render background colour, text display box, continue button
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
                                                        SDL_RenderCopy(renderer, germanButton, NULL, &player1German);
                                                        SDL_RenderCopy(renderer, spanishButton, NULL, &player1Spanish);
                                                        SDL_RenderCopy(renderer, englishButton, NULL, &player2English);
                                                        SDL_RenderCopy(renderer, frenchButton, NULL, &player2French);
                                                        SDL_RenderCopy(renderer, germanButton, NULL, &player2German);
                                                        SDL_RenderCopy(renderer, spanishButton, NULL, &player2Spanish);

							//present all to the screen
							SDL_RenderPresent(renderer);

						}

						else if (x < ((0.7 * this->width) * this->tileWidth)
							&& x
						>((0.6 * this->width) * this->tileWidth)) {

							player2E = false;
							player2F = true;
							player2G = false;
							player2S = false;

							//display this choice to the screen
							this->displayBox->display("Player 2:\nFrench");

							//re-render background colour, text display box, continue button
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
                                                        SDL_RenderCopy(renderer, germanButton, NULL, &player1German);
                                                        SDL_RenderCopy(renderer, spanishButton, NULL, &player1Spanish);
                                                        SDL_RenderCopy(renderer, englishButton, NULL, &player2English);
                                                        SDL_RenderCopy(renderer, frenchButton, NULL, &player2French);
                                                        SDL_RenderCopy(renderer, germanButton, NULL, &player2German);
                                                        SDL_RenderCopy(renderer, spanishButton, NULL, &player2Spanish);

							//present all to the screen
							SDL_RenderPresent(renderer);

						}

						else if (x < ((0.8 * this->width) * this->tileWidth)
                                                        && x
                                                >((0.7 * this->width) * this->tileWidth)) {

                                                        player2E = false;
							player2F = false;
							player2G = true;
							player2S = false;

                                                        //display this choice to the screen
                                                        this->displayBox->display("Player 2:\nGermans");

                                                        //re-render background colour, text display box, continue button
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
                                                        SDL_RenderCopy(renderer, germanButton, NULL, &player1German);
                                                        SDL_RenderCopy(renderer, spanishButton, NULL, &player1Spanish);
                                                        SDL_RenderCopy(renderer, englishButton, NULL, &player2English);
                                                        SDL_RenderCopy(renderer, frenchButton, NULL, &player2French);
                                                        SDL_RenderCopy(renderer, germanButton, NULL, &player2German);
                                                        SDL_RenderCopy(renderer, spanishButton, NULL, &player2Spanish);


                                                        //present all to the screen
                                                        SDL_RenderPresent(renderer);

                                                }

						else if (x < ((0.9 * this->width) * this->tileWidth)
                                                        && x
                                                >((0.8 * this->width) * this->tileWidth)) {

                                                        player2E = false;
							player2F = false;
							player2G = false;
							player2S = true;

                                                        //display this choice to the screen
                                                        this->displayBox->display("Player 2:\nSpanish");

                                                        //re-render background colour, text display box, continue button
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
                                                        SDL_RenderCopy(renderer, germanButton, NULL, &player1German);
                                                        SDL_RenderCopy(renderer, spanishButton, NULL, &player1Spanish);
                                                        SDL_RenderCopy(renderer, englishButton, NULL, &player2English);
                                                        SDL_RenderCopy(renderer, frenchButton, NULL, &player2French);
                                                        SDL_RenderCopy(renderer, germanButton, NULL, &player2German);
                                                        SDL_RenderCopy(renderer, spanishButton, NULL, &player2Spanish);


                                                        //present all to the screen
                                                        SDL_RenderPresent(renderer);

                                                }

					}
				}

			}

			//delete no longer needed assets
			delete continueButton;

			//create new continue button with end player turn text
			Button* turnButton = new Button(
				(this->tileWidth * this->width),
				((this->height - 2) * this->tileHeight), (this->tileHeight * 2), 200
				, continueHandler,
				"Buttons/EndTurn.png", imageHandler);

			delete continueHandler;

			this->continueButton = turnButton;

			this->arr.push_back(new ControlPoint(64, 225, tileHeight, tileWidth));
			this->arr.push_back(new ControlPoint(288, 225, tileHeight, tileWidth));
			this->arr.push_back(new ControlPoint(576, 225, tileHeight, tileWidth));


			//create the players using the above values for faction

			Player* player1;
			int faction = -1;
			if (player1E) {
				faction = 1;
			}
			else if (player1F) {
				faction = 2;
			}
			else if (player1G) {
				faction = 3;
			}
			else if (player1S) {
				faction = 4;
			}
			this->players[0] = new Player(faction, 3, &arr);

			Player* player2;
			if (player2E) {
				faction = 1;
			}
			else if (player2F) {
				faction = 2;
			}
			else if (player2G) {
				faction = 3;
			}
			else if (player2S) {
				faction = 4;
			}
			this->players[1] = new Player(faction, 3, &arr);


			this->bgMap = new backgroundMap(this->tileHeight, this->tileWidth,
				this->width, this->height, this->imageHandler);
			this->fgMap = new foregroundMap(this->tileWidth, this->tileHeight,
				this->width, this->height, this->imageHandler,
				this->displayBox, this->players[0], this->players[1], &arr,this->sa);

			//otherwise, game is now running
			this->isRunning = true;

			//return successfully
			return 0;

		}
		//otherwise, print error and exit as other classes will fail without text display box
		else {

			std::cerr << "The SDL text system failed to initialize."
				<< std::endl;

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


/**@brief Function to handle events that happen on the game window
details This function takes in the event and checks to see if it is a click. 
	If so, it handles it differently depending on the location of the click.
	If the continue button has been pressed (later the end turn button), check to see if either player has won. 
	If they have, display a win screen followed by a credits screen. 
	Else, if no player has won, it switches the current player to the other player. 
	If the click was on the map surface, it passes the event to the foreground map event handler. 

@param  pointer to an SDL event 
@return none
	
*/
void Game::eventHandler(const SDL_Event* event) {

	if (event->type == SDL_MOUSEBUTTONUP) {
		//get the x location of the click
		int x = event->button.x;
		int y = event->button.y;

		//check to see if the continue button has been pressed, if so, set player to next player and proceed
		if ((x < ((this->width * this->tileWidth) + 200))
			&& (x
		> (this->width * this->tileWidth))) {

			if ((y > ((this->height - 2) * this->tileHeight))
				&& y < (this->height * this->tileHeight)) {


				//check to see if the current player has won the game (other player cannot win when not their turn)
				//if other player has no more units, current player has won
				int playerToCheck = (this->currentPlayerIndex % 2) + 1;
				if (this->players[playerToCheck - 1]->noUnit() || this->players[currentPlayerIndex -1]->hasWon()){

					//call the win screen with the current player number passed as a parameter
					doWinScreen(this->currentPlayerIndex);
					//set game to not running so main program ends
					this->isRunning = false;
					return;
				}
				
				
				//otherwise reset the players so that next turn all units can be used then switch players
				else{
				
					this->currentPlayerIndex = (this->currentPlayerIndex % 2) + 1;
					
					this->players[this->currentPlayerIndex - 1]->reset();
	
					//print notification to display that the player has switched
					std::string playerSwitched = "Player " + std::to_string(this->currentPlayerIndex) + " now \nplaying!\nPlayer 1 score: " + std::to_string(this->players[0]->getScore()) + "\nPlayer 2 score: " + std::to_string(this->players[1]->getScore()) + "\n";
					this->displayBox->display(playerSwitched);
				
				}

			}
		}



		//otherwise, make sure the click was in the map area before passing to the map to handl
		if ((x < (this->width * this->tileWidth)) && (x > 0)) {

			if ((y < (this->height * this->tileHeight)) && (y > 0)) {

				this->fgMap->handleEvent(event, this->currentPlayerIndex);

			}

		}

	}
}

/**@brief Function to render the images for the game window
details This function calls render on all visual objects of the game from background up so that it overlays properly. 
	Render functions are called on the background map, foreground map,display box and continue/end turn button owned by the game. 

@param  none
@return none
	
*/
void Game::render() {

	//call render on all objects
	this->bgMap->render();
	this->fgMap->render();
	this->displayBox->render();
	this->continueButton->render();

}



/**@brief Function clears the renderer owned by the game
details This function clears all images from the renderer for the game.

@param  none
@return none
	
*/
void Game::renderClear() {
	SDL_RenderClear(this->renderer);
}


/**@brief Function displays all rendered images to the screen 
details This function displays the rendered images to the screen for this game object. 

@param  none
@return none
	
*/
void Game::renderRepresent() {
	SDL_RenderPresent(this->renderer);
}


/**@brief Function returns a boolean value to represent whether or not the game is currently running
details This function returns a boolean value to represent whether or not the game is currently running. 
	If the game has not been initialized properly, or if a player has won and gone through the win and credits screen, 
	this will return false. Else, it will be true.

@param  none
@return boolean value
	
*/
bool Game::running() {
	return this->isRunning;
}


/**@brief Function creates and displays a screen with the rules of the game to the game window
details This function stores the rules for each area of the game, including the ways to win, how to get info on the units, 
	how to move and attack units, control points, and unit special abilities. These are displayed to the window and then,
	the rules will remain on the screen until the continue button is clicked, when it returns from the function to the original 
	place in the program.

@param  none
@return none
	
*/
void Game::rules() {

	std::string goals = "Goal\nReduce your opponent's army to zero OR get a total of 50 points by maintaining control of the rocks\n";
	std::string info = "Info\nDouble click any unit to get its current statistics\n";
	std::string movement = "Movement\nDuring your turn, a single click on your unit followed by a click on another square will move the unit if the square is within the unit's movement range. A unit cannot be moved after an attack until your next turn.\n";
	std::string attack = "Attack\nDuring your turn, a single click on your unit followed by a click on the opponent's unit will reduce the opponent's unit by the attacking unit's attack score MINUS the defending unit's defense score. The defending unit must be within the attacking unit's attack range.\n";
	std::string controlPts = "\nRocks Control Points\nIf either player has a unit within one square of a rock control point at the end of a turn AND the other player does not have a unit within proximity of the same rock, the score of the player with control of the rock will increase by 2 points.\n";
	std::string specAbil = "Special Abilies\nUnits have special abilities that can be activated by a single right click on your unit. This will change their stats for a certain number of turns. After activation, there is a cooldown period in which the special ability cannot be re-activated. For more info, double click a unit.";
	std::string rules = goals
				+"\n" + info
				+"\n" + movement
				+"\n" + attack
				+"\n" + specAbil
				+"\n" + controlPts;

	//create font to use to display text
	TTF_Font* textFont = TTF_OpenFont("Fonts/CaviarDreams.ttf", 14);

	//set color of the text
	SDL_Color textColor = { 255,255,255 };

	//create rules surface from text, font and colour
	SDL_Surface* textSurface;
	textSurface = TTF_RenderText_Blended_Wrapped(textFont, rules.c_str(), textColor, 500);

	//convert surface to texture and store 
	SDL_Texture* currentDisplay = SDL_CreateTextureFromSurface(this->renderer, textSurface);

	//query the texture to determine size of text
	int textHeight = 0;
	int textWidth = 0;


	//define space that the rules will display to
	SDL_Rect rulesPos;
	rulesPos.x = 25;
	rulesPos.y = 0;

	//query texture to size it properly	
	SDL_QueryTexture(currentDisplay, NULL, NULL, &textWidth, &textHeight);

	rulesPos.h = textHeight;
	rulesPos.w = textWidth;

	//create background image to use under text
	SDL_Surface* backgroundSurface = IMG_Load("Background/ruleBackground.png");

	//then create texture from surface created
	SDL_Texture* backgroundDisplay = SDL_CreateTextureFromSurface(this->renderer, backgroundSurface);

	//render the background and rules
	SDL_RenderClear(this->renderer);

	//display the background to whole screen
	SDL_RenderCopy(this->renderer, backgroundDisplay, NULL, NULL);

	//display the rules to whole screen
	SDL_RenderCopy(this->renderer, currentDisplay, NULL, &rulesPos);

	//display continue button and text display box
	this->continueButton->render();
	this->displayBox->render();

	//present all to the screen
	SDL_RenderPresent(this->renderer);


	//wait until there is an event and check it for an end event
	while (true) {

		SDL_Event event;

		if (SDL_PollEvent(&event)) {
			if (event.type != SDL_MOUSEMOTION && event.type != SDL_MOUSEBUTTONDOWN) {

				//if it is an event that should end the program, call destructor and close the window
				if (event.type == SDL_QUIT
					|| event.type == SDL_WINDOWEVENT_CLOSE) {

					//deinitialize systems
					TTF_Quit();
					SDL_Quit();
					return;
				}



				//if within the continue button, return from the rules screen
				else if (event.type == SDL_MOUSEBUTTONUP) {
					//get the x location of the click
					int x = event.button.x;
					int y = event.button.y;

					//check to see if the continue button has been pressed, if so, set continuepressed to true to break while loop and proceed
					if ((x < ((this->width * this->tileWidth) + 200))
						&& (x > (this->width * this->tileWidth))) {

						if ((y > ((this->height - 2) * this->tileHeight))
							&& y < (this->height * this->tileHeight)) {
							return;

						}
					}

				}
			}
		}
	}
}





/**@brief Function creates and displays a screen congratulating the winning player
details This function constructs a text display congratulating the player that has won (will be determined by the integer value 
	passed into the function) and then this is displayed over a background image until the continue button is clicked. 
	When the continue button is clicked, it goes to the credits screen before returning from the function.

@param  integer value representing which player number has won
@return none
	
*/
void Game::doWinScreen(int playerWon) {

	std::string win = "Congratulations! Player " + std::to_string(playerWon) + " WINS!";

	//create font to use to display text
	TTF_Font* textFont = TTF_OpenFont("Fonts/CaviarDreams_Bold.ttf", 32);

	//set color of the text
	SDL_Color textColor = { 255,255,255 };

	//create rules surface from text, font and colour
	SDL_Surface* textSurface;
	textSurface = TTF_RenderText_Blended_Wrapped(textFont, win.c_str(), textColor, 500);

	//convert surface to texture and store 
	SDL_Texture* currentDisplay = SDL_CreateTextureFromSurface(this->renderer, textSurface);

	//define space that the text will display to
	SDL_Rect winPos;
	winPos.x = 200;
	winPos.y = 100;
	winPos.h = 100;
	winPos.w = 300;

	//create background image to use under text
	SDL_Surface* backgroundSurface = IMG_Load("Background/Background2Final.png");

	//then create texture from surface created
	SDL_Texture* backgroundDisplay = SDL_CreateTextureFromSurface(this->renderer, backgroundSurface);

	//render the background and rules
	SDL_RenderClear(this->renderer);

	//display the background to whole screen
	SDL_RenderCopy(this->renderer, backgroundDisplay, NULL, NULL);

	//display the text to given location
	SDL_RenderCopy(this->renderer, currentDisplay, NULL, &winPos);

	//display continue button and text display box
	this->continueButton->render();
	this->displayBox->render();

	//present all to the screen
	SDL_RenderPresent(this->renderer);


	//wait until there is an event and check it for an end event
	while (true) {

		SDL_Event event;

		if (SDL_PollEvent(&event)) {
			if (event.type != SDL_MOUSEMOTION && event.type != SDL_MOUSEBUTTONDOWN) {

				//if it is an event that should end the program, call destructor and close the window
				if (event.type == SDL_QUIT
					|| event.type == SDL_WINDOWEVENT_CLOSE) {

					//deinitialize systems
					TTF_Quit();
					SDL_Quit();
					return;
				}



				//if within the continue button, close the game
				else if (event.type == SDL_MOUSEBUTTONUP) {
					//get the x location of the click
					int x = event.button.x;
					int y = event.button.y;

					//check to see if the continue button has been pressed, if so, go to the credits screen
					if ((x < ((this->width * this->tileWidth) + 200))
						&& (x > (this->width * this->tileWidth))) {

						if ((y > ((this->height - 2) * this->tileHeight))
							&& y < (this->height * this->tileHeight)) {
							
							//deinitialize systems to end the game
							doCreditScreen();
							return;

						}
					}

				}
			}
		}
	}
}



/**@brief Function displays a credit screen to the game window
details This function constructs a text display with the names of the group members and then this is displayed over a background image until the continue button is clicked. 
	When the continue button is clicked, it ends the game.

@param  none
@return none
	
*/
void Game::doCreditScreen() {

	std::string credits = "Brought to you by:\nAbdallah Alasmar\nOsitadinma Arimah\nJake Nemiroff\nOluwadarasimi Ogunshote\nCarolyn Owen";

	//create font to use to display text
	TTF_Font* textFont = TTF_OpenFont("Fonts/CaviarDreams_Bold.ttf", 32);

	//set color of the text
	SDL_Color textColor = { 0,0,0 };

	//create credits surface from text, font and colour
	SDL_Surface* creditSurface;
	creditSurface = TTF_RenderText_Blended_Wrapped(textFont, credits.c_str(), textColor, 500);

	//convert surface to texture and store 
	SDL_Texture* currentDisplay = SDL_CreateTextureFromSurface(this->renderer, creditSurface);

	//define space that the text will display to
	SDL_Rect creditPos;
	creditPos.x = 200;
	creditPos.y = 100;
	creditPos.h = 300;
	creditPos.w = 300;

	//create background image to use under text
	SDL_Surface* backgroundSurface = IMG_Load("Background/Background2Final.png");

	//then create texture from surface created
	SDL_Texture* backgroundDisplay = SDL_CreateTextureFromSurface(this->renderer, backgroundSurface);

	//render the background and rules
	SDL_RenderClear(this->renderer);

	//display the background to whole screen
	SDL_RenderCopy(this->renderer, backgroundDisplay, NULL, NULL);

	//display the text to given location
	SDL_RenderCopy(this->renderer, currentDisplay, NULL, &creditPos);

	//display continue button and text display box
	this->continueButton->render();
	this->displayBox->render();

	//present all to the screen
	SDL_RenderPresent(this->renderer);


	//wait until there is an event and check it for an end event
	while (true) {

		SDL_Event event;

		if (SDL_PollEvent(&event)) {
			if (event.type != SDL_MOUSEMOTION && event.type != SDL_MOUSEBUTTONDOWN) {

				//if it is an event that should end the program, call destructor and close the window
				if (event.type == SDL_QUIT
					|| event.type == SDL_WINDOWEVENT_CLOSE) {

					//deinitialize systems
					TTF_Quit();
					SDL_Quit();
					return;
				}



				//if within the continue button, close the game
				else if (event.type == SDL_MOUSEBUTTONUP) {
					//get the x location of the click
					int x = event.button.x;
					int y = event.button.y;

					//check to see if the continue button has been pressed, if so, end the game
					if ((x < ((this->width * this->tileWidth) + 200))
						&& (x > (this->width * this->tileWidth))) {

						if ((y > ((this->height - 2) * this->tileHeight))
							&& y < (this->height * this->tileHeight)) {
							
							//deinitialize systems to end the game
							TTF_Quit();
							SDL_Quit();
							return;

						}
					}

				}
			}
		}
	}
}
