#include "Unit.h"

using namespace std;

Unit::Unit(int xPos, int yPos, int height, int width,
		const std::string& imageFile, ImageHandler *imgHandler, int health,
		int offense, int defense, int numOfAttacks, int rangeBegins,
		int rangeEnds, int speed) {
	//set position (offset from upper left of window)
	this->position.x = xPos;
	this->position.y = yPos;

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

const SDL_Rect* Unit::getPosition() {
	return &this->position;
}

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

