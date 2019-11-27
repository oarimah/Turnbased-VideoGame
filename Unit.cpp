/*! \class Unit.cpp
 *  \class which gives the unit a temporary buff in stats based on the paremters passed
 *
 *  \gets the changes in stats and buffs the original stats of the unit for that duration of the time
 *  \uses arguments to get the changes in stats
 *  \author:
 *  \author:
 *  \author:
 *  \author:Osita Arimah
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
#include "Unit.h"

using namespace std;

Unit::Unit(int xPos, int yPos, int height, int width,
		   const std::string& imageFile, ImageHandler *imgHandler, int health,
		   int offense, int defense, int numOfAttacks, int rangeBegins,
		   int rangeEnds, int speed,SpecialAbilities* sa, std::string name) {

	//set position (offset from upper left of window)
this->position.x = xPos;
this->position.y = yPos;
this->sa=sa;
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

// to be used to control the number of thing the unit can do per turn
this->used = false;

//set image handler for this object
this->imageHandler = imgHandler;
//get the Unit image texture from the provided file
this->image = this->imageHandler->loadImage(imageFile);

//nothing has been clicked yet, set to false
this->clicked = false;
}

Unit::~Unit() {
	//delete the image texture that was created for this Tile
	delete this->image;

	//do not delete Tile event as not unique to this Tile
}

// const SDL_Rect* Unit::getPosition() {
// 	return &this->position;
// }

void Unit::changePosition(int newX, int newY) {
	//change the x and y values of the position rectangle to reflect new values
	this->position.x = newX;
	this->position.y = newY;
}

const bool Unit::isClicked() {
	return this->clicked;
}

void Unit::changeClicked(bool value) {
	this->clicked = value;
}

void Unit::changeImage(const std::string& imageFile) {
	SDL_Texture *temp = this->imageHandler->loadImage(imageFile.c_str());
	this->image = temp;
}

void Unit::render() {
	this->imageHandler->render(this->image, &this->position);
}

const string Unit::getType() {
	return "Unit";
}

int Unit::getX(){
	return position.x;
}

int Unit::getY(){
	return position.y;
}

int Unit::getWidth(){
	return position.w;
}

int Unit::getHeight(){
	return position.h;
}

int Unit::getMaxHealth() {
	return this->maxHealth;
}
int Unit::getCurHealth() {
	return this->curHealth;
}

void Unit::setHealth(int damage) {
	this->curHealth -= damage - defense;
	if (this->curHealth < 0)
		this->curHealth = 0;
}

int Unit::getAttack() {
	return this->offense;
}

int Unit::getDefense() {
	return this->defense;
}

int Unit::getMaxNumOfAttacks() {
	return this->numOfAttacksPerTurn;
}

int Unit::getCurNumOfAttacks() {
	return this->numberOfAttacksForTurn;
}

void Unit::attack() {
	this->numberOfAttacksForTurn--;
	this->curSpeed -= this->curSpeed;
	if (this->numberOfAttacksForTurn == 0)
		used = true;
}

int Unit::getRangeBegins() {
	return this->rangeBegins;
}

int Unit::getRangeEnds() {
	return this->rangeEnds;
}

int Unit::getMaxSpeed() {
	return this->maxSpeed;
}

int Unit::getCurSpeed() {
	return this->curSpeed;
}

void Unit::speedUsed(int speedUsed) {
	this->curSpeed -= speedUsed;
	if (this->curSpeed == 0)
		used = true;
}

bool Unit::isUsed() {
	return used;
}

void Unit::reset() {
	this->used = false;
	this->numberOfAttacksForTurn = this->numOfAttacksPerTurn;
	this->curSpeed = this->maxSpeed;
}

bool Unit::isDead() {
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
void Unit::activateAbility() {
    if (!this->sa->isActivated()) {
        this->numOfAttacksPerTurn += this->sa->getChangeInNumAttacks();
        this->rangeBegins += this->sa->getChangeInRangeStarts();
        this->rangeEnds += this->sa->getChangeInRangeEnds();
        this->maxSpeed += this->sa->getChangeInSpeed();
        this->offense += this->sa->getChangeInOffense();
        this->defense += this->sa->getChangeInDefence();
        this->sa->activateAbility();
    } else {
           //do nothing
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
    SpecialAbilities *Unit::getSpecAbil() {
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
    const std::string Unit::getName() {
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
    void Unit::deactivateAbility() {
            this->sa->reset();
            this->offense = this->offense;
            this->defense = this->defense;
            //this->numOfAttacksPerTurn = this->numOfAttacks;
            this->rangeBegins = this->rangeBegins;
            this->rangeEnds = this->rangeEnds;
            //this->maxSpeed = this->speed;
            this->sa->resetStats();
            this->sa->resetAbility();
        }


