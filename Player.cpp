#include "Player.h"

using namespace std;



/**@brief Player class describes a human player of the game 
@author Oluwadarasimi Ogunshote
details This class manages a player's actions, units and win status
	
*/



/**@brief Constructor for a new player object
details This function the faction of the player, the number of control points in the game 
	and a pointer to the vector of control point pointers used in the game. It stores this information and initializes the player's 
	score to 0, defines the points per turn per control point as 2 and the score to win as 50. 

@param 	faction an integer representing which faction the player has selected
@param 	numCP an integer to tell the player how many control points exist in the game
@param 	cp a pointer to a vector of control point pointers that exist in the game

@return a new player object
	
*/
Player::Player(int faction, int numCP, std::vector<ControlPoint *>* cp) {
	this->faction = faction;
	this->numControlPoints = numCP;
	this->cps = cp;
	this->point = 2;
	this->score = 0;
	this->maxScore = 50;
}

/**@brief Destructor for a player object
details This function deallocates the space set aside for each of its units. 
	This is the only dynamically allocated space created within the player object.

@param 	none

@return none
	
*/
Player::~Player() {
	for (int i = 0; i < units.size(); i++)
			delete units[i];
}


/**@brief Checks the player for dead units and erases those that have died.
details This function iterates through the player's units and checks if their health has gone to 0. 
	If so, the unit is deleted and erased from the player's list of units.

@param 	none

@return none
	
*/
void Player::clearDeadUnits() {
	for (int i = 0; i < units.size(); i++)
		if (units[i]->isDead()) {
			delete units[i];
			units.erase(units.begin() + i);
		}
}


/**@brief Used to check if a player has won by score
details This function checks the score of the player against the stored value representing the score required to win. If the 
	player has reached or exceeded this value, the boolean return is true and the player has won. Otherwise, it will return false. 

@param 	none

@return bool representing the player's score indicates a win
	
*/
bool Player::hasWon(){
	return score >= maxScore;
}

/**@brief Getter for the faction indicator of the player
details This function returns an integer value representing which faction this player is (english, french, german, spanish). 

@param 	none

@return an integer representing the faction number of the player
	
*/
int Player::getFaction() {
	return this->faction;
}

/**@brief Function renders all units that this player owns
details This function iterates through the units for the player and and calls the render function for all of them. 

@param 	none

@return none
	
*/
void Player::updateUnits() {
	for (int i = 0; i < units.size(); i++)
		units[i]->render();
	
}

/**@brief Resets all units that the player owns and adds to score as required depending on which control points the player has.
details This function iterates through all of the player's units and calls render on all of them. Then, it checks to see if the units are in 
	proximity to any of the control points and adds 2 points to the score per control point if they are in proximity.  

@param 	none

@return none
	
*/
void Player::reset() {
	for (int i = 0; i < units.size(); i++)
		units[i]->reset();
	for (int j = 0; j < this->numControlPoints; j++)
		for (int i = 0; i < units.size(); i++)
			if (isNext(units[i], (*cps)[j])){
				addToScore();
				break;
			}
}

/**@brief Function adds set points to the player's score
details If the player's score is not the max score, it adds the number of points defined to the player's score.  

@param 	none

@return none
	
*/
void Player::addToScore() {
	if (score != maxScore)
		score += point;
}

/**@brief Returns the player's current score
details This function returns the player's score as an integer. 

@param 	none

@return an integer representing the player's score
	
*/
int Player::getScore(){
	return score;
}

/**@brief Function checks proximity of a unit to a control point 
details This function takes a pointer to a unit and a control point. 
	The difference in the absolute value of the location of the unit and the control point is calculated. If this is less 
	than or equal to 1 (the unit is right next to the control point), the boolean returns as true. Else it will return false. 

@param 	unit a pointer to a unit to check proximity of
@param 	cp a pointer to a control point in the game

@return boolean value representing that the unit is in proximity to the  control point or not
	
*/
bool Player::isNext(Unit* unit, ControlPoint* cp) {
	int x = abs(cp->getX() - unit->getX())/ unit->getWidth();
	int y = abs(cp->getY() - unit->getY())/ unit->getHeight();
	if (x <= 1 && y <= 1)
		return true;
	return false;
}

/**@brief Function adds a unit to the player
details This function takes a pointer to a unit object and adds it to the player's units vector. 

@param 	unit pointer to a unit object

@return none
	
*/
void Player::addUnit(Unit * unit) {
	this->units.push_back(unit);
}

/**@brief Checks to see if the player owns a specific unit
details This function takes a pointer to a unit object and checks for the same unit pointer in the list of the player's units. 
	If it is found, the function returns true. Else, it isn't owned by this player so it returns false. 

@param 	unit a pointer to a unit object

@return boolean representing whether or not the unit is owned by this player
	
*/
bool Player::containsUnit(Unit * unit) {
	for (int i = 0; i < units.size(); i++)
		if (units[i] == unit)
			return true;
	return false;
}

/**@brief Checks to see if the player has no more units
details This function checks the size of the player's units vector. If it is 0, all of the player's units 
	are dead so it will return true. Else, it returns false. 

@param 	none

@return boolean representing whether or not all the player's units are dead
	
*/
bool Player::noUnit() {
	return units.size() == 0;
}
