#include "foregroundMap.h"
#include "UnitFactory.h"


foregroundMap::foregroundMap(int tileWidth, int tileHeight, ImageHandler* imgHandler, TextDisplay* textDisplay, Player* player1, Player* player2)
{
	this->height = tileHeight;
	this->width = tileWidth;
	this->imageHandler = imgHandler;
	this->displayBox = textDisplay;
	this->player1 = player1;
	this->player2 = player2;

	//enter units into the map and each player
	int unitType = 0;
	int faction = this->player1->getFaction();

	//add to first row of the map
	for (int i = 0; i < 20; i++) {
		Unit* unit = UnitFactory::createUnit(i * this->width, 0, this->height, this->width, faction, unitType, this->imageHandler);
		//add unit to player and board
		this->player1->addUnit(unit);
		this->map[i][0] = unit;

		//increment the unit to get a variety of types

		unitType = (unitType + 1) % 3;

	}

	//do the same for the second player
	unitType = 0;
	faction = this->player2->getFaction();

	//add to last row of the map
	for (int i = 0; i < 20; i++) {
		Unit* unit = UnitFactory::createUnit(i * this->width, 19 * this->height, this->height, this->width, faction, unitType, this->imageHandler);
		//add unit to player and board
		this->player2->addUnit(unit);
		this->map[i][19] = unit;

		//increment the unit to get a variety of types
		unitType = (unitType + 1) % 3;

	}

	//set unitClicked to null as no unit on the board has been clicked yet (will be checked in eventhandler)
	this->unitClicked = NULL;
}

foregroundMap::~foregroundMap() {

	for (int i = 0; i < 20, i++) {

		for (int j = 0; j < 20; j++) {

			if (this->map[i][j] != NULL) {

				delete this->map[i][j];
			}
		}
	}

}

void foregroundMap::render()
{
	for (int i = 0; i < 20, i++) {

		for (int j = 0; j < 20; j++) {

			if (this->map[i][j] != NULL) {

				this->map[i][j]->render();
			}
		}
	}

}



void foregroundMap::eventHandler(SDL_Event* event, int player)
{

	//check that the event was a mouse click
	if (event->type == SDL_MOUSEBUTTONUP) {

		//get the x location of the click
		int x = event->button.x;
		int y = event->button.y;

		//get the indexes associated with those locations
		int xIndex = x / this->width;
		int yIndex = y / this->height;

		Unit* clicked = this->map[x][y];

		//if index is empty and a unit clicked previously, see if the unit can move to that location (in range?)
		if (clicked == NULL && this->unitClicked != NULL) {

			//if in range of the unit, move the unit
			if (this->unitClicked->getSpeed() <= ((this->clickedX - x) + (this->clickedY - y))) {

				//change location of unit on map to clicked space
				this->map[x][y] = this->unitClicked;

				//change location of unit in unit
				this->unitClicked->changePosition(x * this->width, y * this->height);

				//remove the unit from clicked
				this->unitClicked = NULL;

			}

		}

		//if index has another unit of the other player's and a unit was clicked previously, attack the other unit
		else if (clicked != NULL && this->unitClicked != NULL) {

			//if this is player 1's turn and the other unit clicked was player 2's, attack
			if (player == 1 && this->player2->containsUnit((Unit*)clicked)) {

				clicked->setHealth(this->unitClicked->getAttack());

				//if unit died, remove it from the board 
				if (clicked->isDead()) {
					this->map[x][y] = NULL;
				}

				//clear dead units of both players
				this->player1->clearDeadUnits();
				this->player2->clearDeadUnits();

				//move the prev clicked unit to the old unit's location on the board
				this->unitClicked->changePosition(x * this->width, y * this->height);
				this->map[x][y] = this->unitClicked;

				//clear the unit clicked
				this->unitClicked = NULL;
			}


		}

		//if the square is not empty and it is a double click, display the info about the unit
		else if (clicked != NULL && event->button.clicks == 2) {

			//construct info for the text display
			std::string info = "Health: " + clicked->getHealth() + "\nAttack Power: " + clicked->getAttack() + "\nDefense Power: " + clicked->getDefense() + "\nRange: " + clicked->getSpeed() + "\n";

			//pass this to the text display
			this->displayBox->display(info);

		}


		//if the unit clicked is the current player's add it to the unit clicked for next time
		else {

			//check the unit's owner
			if (player == 1) {

				//if the unit is owned by player 1, add it to clicked as well as the index
				if (this->player1->containsUnit(clicked)) {

					this->unitClicked = clicked;
					this->clickedX = x;
					this->clickedY = y;

				}
			}

			else {

				//if unit owned by player 2, do the same
				if (this->player2->containsUnit(clicked)) {

					this->unitClicked = clicked;
					this->clickedX = x;
					this->clickedY = y;

				}
			}
		}
	}
}

