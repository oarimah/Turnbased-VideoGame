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
	this->health = health;
	this->offense = offense;
	this->defense = defense;
	this->numOfAttacks = numOfAttacks;
	this->rangeBegins = rangeBegins;
	this->rangeEnds = rangeEnds;
	this->speed = speed;

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

int Unit::getHealth() {
	return this->health;
}

void Unit::setHealth(int damage) {
	this->health -= damage - defense;
	if (this->health < 0)
		this->health = 0;
}

int Unit::getAttack() {
	return this->offense;
}

int Unit::getDefense() {
	return this->defense;
}

int Unit::getNumOfAttacks() {
	return this->numOfAttacks;
}

int Unit::getRangeBegins() {
	return this->rangeBegins;
}

int Unit::getRangeEnds() {
	return this->rangeEnds;
}

int Unit::getSpeed() {
	return this->speed;
}

bool Unit::isDead() {
	return this->health == 0;
}

