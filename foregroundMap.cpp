#include "foregroundMap.h"

/**@brief Class describes the top layer of the game map
@author Carolyn Owen
@author Jake Nemiroff
@author Oluwadarasimi Ogunshote
details The class contains the units on a 2D vector and manages event handling when the map area is clicked on. 
	The vector containing the units uses pointers to unit objects which are owned by players of the game. 
	All events/clicks on the main map are handled by the foreground map event handler which allows units to move, 
	attack, die, display their information or initiate and manage special abilities.

@param  none
@return none	
*/

/**@brief Constructor for a foreground map object
details This function takes the size parameters of the desired map, pointers to image handler and text display box to use, 
	the players of the game and a vector pointing to the control points on the map.
	When it is called, the constructor stores the given values and then populates the 2d vector representing the map with 
	either null pointers or unit pointers. The units for each player are created here and added to either player. Player 1's units 
	are populated to the top row of the map and player 2's units are populated to the bottom row of the map. Then, it sets the last 
	clicked unit pointer to null to represent that no unit on the board has been clicked on yet. 

@param  integer value of the tile width in pixels
@param	integer value of the tile height in pixels
@param 	integer value of the number of rows in the map
@param 	integer value of the number of columns in the map
@param 	pointer to the image handler to use to render objects to the game window
@param	pointer to the text display box to use to display unit stats and notifications to the player
@param 	pointer to player 1
@param	pointer to player 2
@param 	pointer to a vector of control point pointers to use in calculating score

@return a new foreground map object
	
*/
foregroundMap::foregroundMap(
		// @suppress("Class members should be properly initialized")
		int tileWidth, int tileHeight, int numRow, int numColumn,
		ImageHandler* imgHandler, TextDisplay* textDisplay, Player* player1,

		Player* player2, std::vector<ControlPoint *>* cp,SpecialAbilities* sa) {

	this->height = tileHeight;
	this->width = tileWidth;
	this->numTilesWide = numRow;
	this->numTilesHigh = numColumn;
	this->imageHandler = imgHandler;
	this->displayBox = textDisplay;
	this->player1 = player1;
	this->player2 = player2;

	this->cp = cp;
	this->sa=sa;

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

	for (int i = 0; i < 20; i += 3) {
		Unit* unit = UnitFactory::createUnit(i * this->width, 0, this->height,this->width, 1, faction, unitType, this->imageHandler,sa);


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

	for (int i = 0; i < 20; i += 3) {
		Unit* unit = UnitFactory::createUnit(i * this->width, 19 * this->height,
											 this->height, this->width, 2, faction, unitType,

											 this->imageHandler,sa);

		//add unit to player and board
		this->player2->addUnit(unit);
		this->map[i][0][19] = unit;


		//increment the unit to get a variety of types
		unitType = (unitType + 1) % 3;

	}

//set unitClicked to null as no unit on the board has been clicked yet (will be checked in eventhandler)
	this->unitClicked = NULL;
}

/**@brief Destructor for a foreground map
details This function deletes all null or unit pointers that were created for the map. 
	Each square of the map will be deallocated in a loop.

@param  none
@return none
*/
foregroundMap::~foregroundMap() {
	for (int i = 0; i < this->numTilesWide; i++)
		delete this->map[i];
}

/**@brief Function to render the images of the foreground map
details This function calls the updateUnits function on both players, which in turn manages unit changes 
	and then renders them to the game window. The unit textures will be rendered to the correct location on the map because 
	the foreground map event handler changes the internal position of each unit as needed when they move on the map. 

@param  none
@return none
	
*/
void foregroundMap::render() {
	this->player1->updateUnits();
	this->player2->updateUnits();
}

/**@brief Function to handle event that happens within the space of the game map
details This function checks that the event was a mouse click, then compares the location of the 
	click to the vectors to see what was in the square clicked on. The handler then goes through multiple click 
	combination scenarios to determine which action to take. See below for scenarios:

	clicked index is empty (no unit on the square) and a unit of this player's was clicked previously 
		-> see if the unit can move to that location (in range?)
		-> if in range, the unit has enough movement left for this turn and the unit isn't trying to move on top of a control point, 
		   move the unit to the new index in the vector and reset the unit's internal position information

	an empty tile was clicked with nothing being clicked before
		-> do nothing

	a unit was right clicked 
		-> check if the unit is owned by the current player
		-> if it is, try to activate the unit's special ability with the unit's triggering function

	the square contains a unit and it is a double click
		-> display the info about the unit in the foreground map's text display box

	clicked index has a unit of the other player's and a unit owned by the current player was clicked previously
		-> check that the other player's unit is within attack range of the player's unit
		-> check that the attacking unit has attacks left for this turn
		-> attack the other unit
		-> check for dead units and remove them from the player object as well as the foreground map if so
		-> clear the pointer to the last clicked unit for the player's next move

	unit clicked is the current player's 
		-> if the unit has already been used up for this turn, let the player know and don't store info about this unit 
		-> otherwise add it to the unit clicked pointer for next time 

	
	
@param  pointer to the SDL event that happened on the map's area
@param 	integer representing the number of the current player to use in checking who owns a clicked unit
@return none
*/
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

		//if index is empty and a unit clicked previously, see if the unit can move to that location (in range?)
		if ((!clicked) && this->unitClicked != NULL) {

			bool forbidden = false;

			//check to make sure that the unit isn't trying to move onto a control point
			for (int i = 0; i < (*cp).size(); i++){

				if ((((*cp)[i]->getX() / this->width) == xIndex) && (((*cp)[i]->getY() / this->height) == yIndex)){
					forbidden = true;

					//print notification of forbidden move to player
					this->displayBox->display("The unit cannot move on\ntop of a control point");
					break;
				}

			}


			//otherwise, check the range of the unit
			if (!forbidden && this->unitClicked->getCurSpeed()
							  >= (abs(this->clickedX - xIndex)
								  + abs(this->clickedY - yIndex))) {

				this->unitClicked->speedUsed(
						(abs(this->clickedX - xIndex)
						 + abs(this->clickedY - yIndex)));

				//change location of unit on map to clicked space
				this->map[xIndex][0][yIndex] = this->unitClicked;

				//make sure old location points to null
				this->map[clickedX][0][clickedY] = 0;

				//change location of unit in unit
				this->unitClicked->changePosition(xIndex * this->width,
												  yIndex * this->height);

				//remove the unit from clicked
				this->unitClicked = NULL;
				this->clickedX = 0;
				this->clickedY = 0;

			}

				//if the above failed but the square is not a control point, it is out of range, so let the player know
			else if (!forbidden){

				this->displayBox->display("The unit cannot move\nthat far!");
			}


		}

			//if an empty tile was clicked with nothing being clicked before, do nothing
		else if (!clicked && this->unitClicked == NULL) {

		}



			//activate a special ability for a specific unit with a right click
		else if (event->button.button == SDL_BUTTON_RIGHT) {

				if ((player == 1 && this->player1->containsUnit(clicked)) ||
					(player == 2 && this->player2->containsUnit(clicked)))  {

						if(!clicked->getSpecAbil()->isActivated()){
							clicked->activateAbility();
						} else{
							if (clicked->getSpecAbil()->effectTurns())
								this->displayBox->display("This unit's special ability is already in effect.\n");	
							else
								this->displayBox->display("This unit's special ability is on cooldown.\n");	
								
						}
				} else {
					this->displayBox->display("This unit does not belong to you!\n");
				
				}
		}

		//if the square is not empty and it is a double click, display the info about the unit
		else if (clicked && event->button.clicks == 2) {


			//construct info for the text display

			SpecialAbilities * clickedSA = clicked->getSpecAbil();

			std::string info = clicked->getName()
							+ "\n"
							+ "\nMax Health: "

							   + std::to_string(clicked->getMaxHealth())
							   + "\nCurrent Health: "
							   + std::to_string(clicked->getCurHealth())
							   + "\nAttack Power: "
							   + std::to_string(clicked->getAttack())
							   + "\nAttack Range: "
							   + std::to_string(clicked->getRangeBegins()) + " to " +
							   std::to_string(clicked->getRangeEnds())
							   + "\nMax Number of Attacks: "
							   + std::to_string(clicked->getMaxNumOfAttacks())
							   + "\nAttacks Left: "
							   + std::to_string(clicked->getCurNumOfAttacks())
							   + "\nDefense Power: "
							   + std::to_string(clicked->getDefense())
							   + "\nMovement: "
							   + std::to_string(clicked->getMaxSpeed())
							   + "\nMovement Left: "
							   + std::to_string(clicked->getCurSpeed())
							   + "\n"


			+ "\nSpecial ability buffs \nDefense: "
			+ std::to_string(clickedSA->getChangeInDefence())
			+ "\nOffense: "
			+ std::to_string(clickedSA->getChangeInOffense())
			+ "\nAttack Range: "
			+ std::to_string(clickedSA->getChangeInRangeStarts())
			+ "-"
			+ std::to_string(clickedSA->getChangeInRangeEnds())
			+ "\nNum Attacks: "
			+ std::to_string(clickedSA->getChangeInNumAttacks())
			+ "\nMovement: "
			+ std::to_string(clickedSA->getChangeInSpeed())
			+ "\nTurns for Effect: "
			+ std::to_string(clickedSA->effectTurns())
			+ "\nCooldown turns: "
			+ std::to_string(clickedSA->coolDownTurns())
			+ "\n_";

			
			//pass this to the text display
			this->displayBox->display(info);

		}

			//if index has another unit of the other player's and a unit was clicked previously, attack the other unit

		else if (clicked && this->unitClicked != NULL) {


			//if this is player 1's turn and the other unit clicked was player 2's, attack
			if ((player == 1 && this->player2->containsUnit(clicked))
				|| (player == 2 && this->player1->containsUnit(clicked))) {
				int distance = abs(this->clickedX - xIndex)
							   + abs(this->clickedY - yIndex);
				if ((this->unitClicked->getRangeBegins() <= distance)
					&& (this->unitClicked->getRangeEnds() >= distance)) {
					this->unitClicked->attack();
					clicked->setHealth(this->unitClicked->getAttack());
					//if unit died, remove it from the board
					if (clicked->isDead()) {
						this->map[xIndex][0][yIndex] = NULL;
					}

					//clear dead units of both players
					this->player1->clearDeadUnits();
					this->player2->clearDeadUnits();

					//clear the unit clicked
					this->unitClicked = NULL;
				} else {

					//the attack can't be done, display notification to the user on the display box
					this->displayBox->display("Unit is out\nof attack range! \nDouble click on unit\nfor more info!");
				}
			}
				//otherwise, it is one of the players own units, so change the unit clicked of the player
			else {

				this->unitClicked = clicked;
				this->clickedX = xIndex;
				this->clickedY = yIndex;
			}

		}

			//if the unit clicked is the current player's add it to the unit clicked for next time
		else {

			//check the unit's owner
			if (player == 1) {

				//if the unit is owned by player 1, add it to clicked as well as the index
				if (this->player1->containsUnit(clicked)
					&& !clicked->isUsed()) {

					this->unitClicked = clicked;
					this->clickedX = xIndex;
					this->clickedY = yIndex;

					//clear the text display box in case an ineligible unit was clicked before
					this->displayBox->display("");

				}

					//if the unit has been used, let the player know that they can't use it again
				else if (this->player1->containsUnit(clicked)
						 && clicked->isUsed()){

					this->displayBox->display("This unit cannot be used\nagain during this turn.");
				}
			}

			else {

				//if unit owned by player 2, do the same
				if (this->player2->containsUnit(clicked)
					&& !clicked->isUsed()) {

					this->unitClicked = clicked;
					this->clickedX = xIndex;
					this->clickedY = yIndex;

					//clear the text display box in case an ineligible unit was clicked before
					this->displayBox->display("");

				}

					//if the unit has been used, let the player know that they can't use it again
				else if (this->player2->containsUnit(clicked)
						 && clicked->isUsed()){

					this->displayBox->display("This unit cannot be used\nagain during this turn.");
				}
			}
		}
	}
}



/**@brief Function to return a string representing the type of object
details This function returns a string with the name foregroundMap to let the caller know that this is a foreground map type object. 
	This function complies with the required functions of a game object. 

@param  none
@return constant string 
	
*/
const std::string foregroundMap::getType() {

	return "foregroundMap";
}