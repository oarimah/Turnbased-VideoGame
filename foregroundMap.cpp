#include "foregroundMap.h"
#include "UnitFactory.h"

foregroundMap::foregroundMap(
		// @suppress("Class members should be properly initialized")
		int tileWidth, int tileHeight, int numRow, int numColumn,
		ImageHandler* imgHandler, TextDisplay* textDisplay, Player* player1,
		Player* player2) {
	this->height = tileHeight;
	this->width = tileWidth;
	this->numTilesWide = numRow;
	this->numTilesHigh = numColumn;
	this->imageHandler = imgHandler;
	this->displayBox = textDisplay;
	this->player1 = player1;
	this->player2 = player2;

	// initialize the map and set everything to NULL
	for (int i = 0; i < numRow; i++) {
		this->map.push_back(new std::vector<Unit*>);
		for (int j = 0; j < numColumn; j++) {
			this->map[i]->push_back(NULL);
		}
	}

//enter units into the map and each player
	int unitType = 0;
	int faction = this->player1->getFaction();

//add to first row of the map
	for (int i = 0; i < 20; i++) {
		Unit* unit = UnitFactory::createUnit(i * this->width, 0, this->height,
				this->width, faction, unitType, this->imageHandler);
		//add unit to player and board
		this->player1->addUnit(unit);
		this->map[i][0][0] = unit;

		//increment the unit to get a variety of types

		unitType = (unitType + 1) % 3;

	}

//do the same for the second player
	unitType = 0;
	faction = this->player2->getFaction();

//add to last row of the map
	for (int i = 0; i < 20; i++) {
		Unit* unit = UnitFactory::createUnit(i * this->width, 19 * this->height,
				this->height, this->width, faction, unitType,
				this->imageHandler);
		//add unit to player and board
		this->player2->addUnit(unit);
		this->map[i][0][1] = unit;

		//increment the unit to get a variety of types
		unitType = (unitType + 1) % 3;

	}

//set unitClicked to null as no unit on the board has been clicked yet (will be checked in eventhandler)
	this->unitClicked = NULL;
}

foregroundMap::~foregroundMap() {
	for (int i = 0; i < this->numTilesWide; i++)
		delete this->map[i];
}

void foregroundMap::render() {
	this->player1->updateUnits();
	this->player2->updateUnits();
}

void foregroundMap::handleEvent(const SDL_Event* event, int player) {
//check that the event was a mouse click
	if (event->type == SDL_MOUSEBUTTONUP) {

		//get the x location of the click
		int x = event->button.x;
		int y = event->button.y;

		//get the indexes associated with those locations
		int xIndex = x / this->width;
		int yIndex = y / this->height;


		Unit* clicked = this->map[xIndex][0][yIndex];
		std::cout << "Got Here" << std::endl;

		//if index is empty and a unit clicked previously, see if the unit can move to that location (in range?)
		if (clicked == NULL && this->unitClicked != NULL) {

			//if in range of the unit, move the unit
			if (this->unitClicked->getSpeed()
					<= (abs(this->clickedX - xIndex) + abs(this->clickedY - yIndex))) {

				//change location of unit on map to clicked space
				this->map[x][0][y] = this->unitClicked;

				//change location of unit in unit
				this->unitClicked->changePosition(xIndex * this->width,
						yIndex * this->height);

				//remove the unit from clicked
				this->unitClicked = NULL;

			}

		}

		//if index has another unit of the other player's and a unit was clicked previously, attack the other unit
		else if (clicked != NULL && this->unitClicked != NULL) {

			//if this is player 1's turn and the other unit clicked was player 2's, attack
			if (player == 1 && this->player2->containsUnit((Unit*) clicked)) {

				clicked->setHealth(this->unitClicked->getAttack());

				//if unit died, remove it from the board
				if (clicked->isDead()) {
					this->map[xIndex][0][yIndex] = NULL;
				}

				//clear dead units of both players
				this->player1->clearDeadUnits();
				this->player2->clearDeadUnits();

				//move the prev clicked unit to the old unit's location on the board
				this->unitClicked->changePosition(xIndex * this->width,
						yIndex * this->height);
				this->map[xIndex][0][yIndex] = this->unitClicked;

				//clear the unit clicked
				this->unitClicked = NULL;
			}

		}

		//if the square is not empty and it is a double click, display the info about the unit
		else if (clicked != NULL && event->button.clicks == 2) {

			//construct info for the text display
			std::string info = "Health: " + std::to_string(clicked->getHealth())
					+ "\nAttack Power: " + std::to_string(clicked->getAttack())
					+ "\nDefense Power: "
					+ std::to_string(clicked->getDefense()) + "\nRange: "
					+ std::to_string(clicked->getSpeed()) + "\n";

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
					this->clickedX = xIndex;
					this->clickedY = yIndex;

				}
			}

			else {

				//if unit owned by player 2, do the same
				if (this->player2->containsUnit(clicked)) {

					this->unitClicked = clicked;
					this->clickedX = xIndex;
					this->clickedY = yIndex;

				}
			}
		}
	}
}

const std::string foregroundMap::getType() {

	return "foregroundMap";
}
