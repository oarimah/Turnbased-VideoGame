
#include "Unit.h"

using namespace std;

/*! \class Unit.cpp
 *  \class which gives the unit a temporary buff in stats based on the paremters passed
 *
 *  \gets the changes in stats and buffs the original stats of the unit for that duration of the time
 *  \uses arguments to get the changes in stats
 *  \author Oluwadarasimi Ogunshote
 *  \author Osita Arimah
 *  \author Jake Nemiroff
 *  \param xPos, x-coordinate of the unit
 *  \param yPos; y-coordinate of the unit
 *  \param width; width of the unit
 *  \param height; height of the unit
 *  \param imageFile; image of the unit
 *  \param health; health of the unit
 *  \param offense; offense of the unit
 *  \param defense; defense of the unit
 *  \param numOfAttacks; number of attacks per turn for the unit
 *  \param rangeBegins; range begins for the unit
 *  \param rangeEnds; range ends for the unit
 *  \param speed; speed for the unit
 *  \param sa, special abilities object
 *  \param name; name of the unit
 *  \return the initialized unit;
 */

/**
 * Constructor for the unit class
 *
 * initialize the unit with the stats passed as the parameter
 *
 *
 * @param the stats of the unit
 * @return an initialized  unit with the stats
 */
Unit::Unit(int xPos, int yPos, int height, int width,
		   const std::string &imageFile, ImageHandler *imgHandler, int health,
		   int offense, int defense, int numOfAttacks, int rangeBegins,
		   int rangeEnds, int speed, SpecialAbilities *sa, std::string name)
{

	//set position (offset from upper left of window)
	this->position.x = xPos;
	this->position.y = yPos;
	this->sa = sa;

	//set size of the image
	this->position.h = height;
	this->position.w = width;

	//stats of the unit
	this->maxHealth = health;
	this->curHealth = health;
	this->offense = offense;
	this->defense = defense;
	this->numOfAttacksPerTurn = numOfAttacks;
	this->numberOfAttacksForTurn = numOfAttacks;
	this->rangeBegins = rangeBegins;
	this->rangeEnds = rangeEnds;
	this->maxSpeed = speed;
	this->curSpeed = speed;

	this->name = name;

	// to be used to control the number of thing the unit can do per turn
	this->used = false;

	//set image handler for this object
	this->imageHandler = imgHandler;
	//get the Unit image texture from the provided file
	this->image = this->imageHandler->loadImage(imageFile);

	//nothing has been clicked yet, set to false
	this->clicked = false;
}

/**
 * Destructor for the unit class
 *
 * delete the image texture
 *
 *
 * @param none
 * @return none; just delete the image
 */
Unit::~Unit()
{
	//delete the image texture that was created for this Tile
	delete this->image;

	//do not delete Tile event as not unique to this Tile
}

/**
 * void Unit::changePosition(int newX, int newY)
 *
 * changes the position of the unit based on the parameters passed
 *
 *
 * @param newX and newY which is the new co ordinates of the unit
 * @return none; just change the position of the unit
 */
void Unit::changePosition(int newX, int newY)
{
	//change the x and y values of the position rectangle to reflect new values
	this->position.x = newX;
	this->position.y = newY;
}

/**
 * const bool Unit::isClicked()
 *
 * checks if the unit has been clicked
 *
 *
 * @param none
 * @return bool value which indicates whether the unit has been clicked or not
 */
const bool Unit::isClicked()
{
	return this->clicked;
}

/**
 * void Unit::changeClicked(bool value)
 *
 * changes the clicked variable which indicates whether a unit has been clicked or not
 *
 *
 * @param bool value
 * @return none; changes the value of clicked to the parameter
 */
void Unit::changeClicked(bool value)
{
	this->clicked = value;
}

/**
 * void Unit::changeImage(const std::string &imageFile)
 *
 * changes the image file that is loaded for the image
 *
 *
 * @param imageFile; which is the new image
 * @return none; simply change the image
 */
void Unit::changeImage(const std::string &imageFile)
{
	SDL_Texture *temp = this->imageHandler->loadImage(imageFile.c_str());
	this->image = temp;
}

/**
 * void Unit::render()
 *
 * this function renders the image of the unit
 *
 *
 * @param none
 * @return none; render the image when function is called
 */
void Unit::render()
{
	this->imageHandler->render(this->image, &this->position);
}

/**
 * const string Unit::getType()
 *
 * this function gets the type
 *
 *
 * @param none
 * @return "Unit"
 */
const string Unit::getType()
{
	return "Unit";
}

/**
 * int Unit::getX()
 *
 * gets the x coordinate of the unit
 *
 *
 * @param none
 * @return the x co ordinate of the unit
 */
int Unit::getX()
{
	return position.x;
}

/**
 * int Unit::getY()
 *
 * gets the y coordinate of the unit
 *
 *
 * @param none
 * @return the y co ordinate of the unit
 */
int Unit::getY()
{
	return position.y;
}

/**
 * int Unit::getWidth()
 *
 * gets the width of the unit
 *
 *
 * @param none
 * @return the width of the unit
 */
int Unit::getWidth()
{
	return position.w;
}

/**
 * int Unit::getHeight()
 *
 * gets the height of the unit
 *
 *
 * @param none
 * @return the height of the unit
 */
int Unit::getHeight()
{
	return position.h;
}

/**
 * int Unit::getMaxHealth()
 *
 * gets the maximum health of the unit
 *
 *
 * @param none
 * @return the max health of the unit
 */
int Unit::getMaxHealth()
{
	return this->maxHealth;
}

/**
 * int Unit::getCurHealth()
 *
 * gets the current health of the unit
 *
 *
 * @param none
 * @return the current health of the unit
 */
int Unit::getCurHealth()
{
	return this->curHealth;
}

/**
 * void Unit::setHealth(int damage)
 *
 * set the health of the unit based on the damage the unit takes
 *
 *
 * @param damage that the unit will take
 * @return none; just sets the new damage
 */
void Unit::setHealth(int damage)
{
	this->curHealth -= damage - defense;
	if (this->curHealth < 0)
		this->curHealth = 0;
}

/**
 * int Unit::getAttack()
 *
 *  get the offense of the unit
 *
 *
 * @param none
 * @return the offense of the unit
 */
int Unit::getAttack()
{
	return this->offense;
}

/**
 * int Unit::getDefense()
 *
 *  get the defense of the unit
 *
 *
 * @param none
 * @return the defense of the unit
 */
int Unit::getDefense()
{
	return this->defense;
}

/**
 * int Unit::getMaxNumOfAttacks()
 *
 *  get the max number of attacks for the unit
 *
 *
 * @param none
 * @return the number of attacks for the unit
 */
int Unit::getMaxNumOfAttacks()
{
	return this->numOfAttacksPerTurn;
}

/**
 * int Unit::getCurNumOfAttacks()
 *
 *  get the current number of attacks for the unit
 *
 *
 * @param none
 * @return the number of attacks for the unit
 */
int Unit::getCurNumOfAttacks()
{
	return this->numberOfAttacksForTurn;
}

/**
 * Unit::attack()
 *
 *  handle the number of attacks and the current speed when the unit is attacking
 *
 *
 * @param none
 * @return none; just update the unit's stats
 */
void Unit::attack()
{
	this->numberOfAttacksForTurn--;
	this->curSpeed -= this->curSpeed;
	if (this->numberOfAttacksForTurn == 0)
		used = true;
}

/**
 * int Unit::getRangeBegins()
 *
 *  get the range begins variable stat from the unit
 *
 *
 * @param none
 * @return the rangeBegins for the unit
 */
int Unit::getRangeBegins()
{
	return this->rangeBegins;
}

/**
 * int Unit::getRangeEnds()
 *
 *  get the range ends variable stat from the unit
 *
 *
 * @param none
 * @return the rangeEnds for the unit
 */
int Unit::getRangeEnds()
{
	return this->rangeEnds;
}

/**
 * int Unit::getMaxSpeed()
 *
 *  get the max speed variable stat from the unit
 *
 *
 * @param none
 * @return the max speed for the unit
 */
int Unit::getMaxSpeed()
{
	return this->maxSpeed;
}

/**
 * int Unit::getCurSpeed()
 *
 *  get the current speed variable stat from the unit
 *
 *
 * @param none
 * @return the current speed for the unit
 */
int Unit::getCurSpeed()
{
	return this->curSpeed;
}

/**
 * void Unit::speedUsed(int speedUsed)
 *
 *  change the current speed of the unit based on the speed used
 *
 *
 * @param speedUsed
 * @return none; just update the current speed of the unit
 */
void Unit::speedUsed(int speedUsed)
{
	this->curSpeed -= speedUsed;
	if (this->curSpeed == 0)
		used = true;
}

/**
 * bool Unit::isUsed()
 *
 *  check  the used bool variable
 *
 *
 * @param none
 * @return used, bool variable
 */
bool Unit::isUsed()
{
	return used;
}

/**
 * void Unit::reset()
 *
 *  reset the stats of the unit when deactivating the special abilities
 *
 *
 * @param none
 * @return none; just update the unit's stats
 */
void Unit::reset()
{
	this->used = false;
	this->sa->reset();
	this->deactivateAbility();
	this->numberOfAttacksForTurn = this->numOfAttacksPerTurn;
	this->curSpeed = this->maxSpeed;
}

/**
 * bool Unit::isDead()
 *
 *  check if the unit's health is 0
 *
 *
 * @param none
 * @return if the current health is 0
 */
bool Unit::isDead()
{
	return this->curHealth == 0;
}

/**
 * void Unit::activateAbility()
 *
 * Activate the special ability for the unit
 *
 *
 * @param none
 * @return none; just activate the ability for the unit and reset the ability
 */
void Unit::activateAbility()
{
	if (!this->sa->isActivated())
	{
		this->numOfAttacksPerTurn += this->sa->getChangeInNumAttacks();
		this->numberOfAttacksForTurn += this->sa->getChangeInNumAttacks();
		this->rangeBegins += this->sa->getChangeInRangeStarts();
		this->rangeEnds += this->sa->getChangeInRangeEnds();
		this->maxSpeed += this->sa->getChangeInSpeed();
		this->curSpeed += this->sa->getChangeInSpeed();
		this->offense += this->sa->getChangeInOffense();
		this->defense += this->sa->getChangeInDefence();
		this->sa->activateAbility();
	}
}

/**
    * SpecialAbilities *Unit::getSpecAbil()
    *
    * get the special ability of the unit
    *
    *
    * @param none
    * @return the special ability of the unit
    */
SpecialAbilities *Unit::getSpecAbil()
{
	return this->sa;
}

/**
    * const std::string Unit::getName()
    *
    * get the name of the type of unit
    *
    *
    * @param none
    * @return return the name of the unit
    */
const std::string Unit::getName()
{
	return this->name;
}

/**
    * void Unit::deactivateAbility()
    *
    * Deactivate the special ability for the unit
    *
    *
    * @param none
    * @return none; just deactivate the ability for the unit and reset the ability
    */

void Unit::deactivateAbility()
{
	if (sa->isStatsReset())
	{
		this->offense -= this->sa->getChangeInOffense();
		this->defense -= this->sa->getChangeInDefence();
		this->numOfAttacksPerTurn -= this->sa->getChangeInNumAttacks();
		this->rangeBegins -= this->sa->getChangeInRangeStarts();
		this->rangeEnds -= this->sa->getChangeInRangeEnds();
		this->maxSpeed -= this->sa->getChangeInSpeed();
	}
}
