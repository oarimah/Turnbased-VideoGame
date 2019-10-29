#include "Game.h"



Game::Game(int numTilesHigh, int numTilesWide) {

	//make height equal to the number of tiles times the tile height, plus 200 for the display text box at the bottom
	this->height = numTilesHigh * TILE_HEIGHT + 200;

	//set width equal to the number of tiles times the tile width
	this->width = numTilesWide * TILE_WIDTH;

	//set image handler to null as not initialized  yet
	this->imageHandler = NULL;

	//set running to false because init has not been called yet
	isRunning = false;

}




Game::~Game() {

	//call destructors on all things created (both map layers, renderer, window)

}

int Game::init() {



	//initialize all systems for graphics handling

	//if can initialize SDL system, make a window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		SDL_Window* window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_SHOWN);
	
		//make renderer for the window using first available driver and no flags
		this->renderer = SDL_CreateRenderer(window, -1, 0);

		//create imageHandler with this renderer
		this->imageHandler = new ImageHandler(renderer);
	
	}

	//otherwise, print a notification of failure and exit (can't go ahead without things initializing properly)
	else {
		std::cerr << "The SDL system failed to initialize." << std::endl;
	}

	//next try to initialize the text system for use with the text display box
	if (TTF_Init() == 0) {

		//create new text display box and locate it at bottom of map (make 2 tiles smaller in width to allow for continue button space under map)
		this->displayBox = new TextDisplay("", 0, (this->height * TILE_HEIGHT), 200, (this->width - (2 * TILE_WIDTH)), renderer);
	}

	//otherwise, print error and exit as other classes will fail without text display box
	else {

		std::cerr << "The SDL text system failed to initialize." << std::endl;
		return -1;
	}

	//otherwise, game is now running
	this->isRunning = true;
	
	return 0;
}



void Game::eventHandler(const SDL_Event* event) {

}



//render both layers of maps of the game
void Game::render() {



	//clear renderer
	SDL_RenderClear(this->renderer);

	//call render on all objects


	//update the window with the newly rendered image above
	SDL_RenderPresent(this->renderer);
}

const bool Game::running()
{
	return this->isRunning;
}


