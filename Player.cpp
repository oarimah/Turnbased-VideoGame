#include "Player.h"

using namespace std;

Player::Player(int faction, int numCP, std::vector<ControlPoint *>* cp) {
	this->faction = faction;
	this->numControlPoints = numCP;
	this->cps = cp;
	this->point = 2;
	this->score = 0;
	this->maxScore = 50;
}

Player::~Player() {
	for (int i = 0; i < units.size(); i++)
		if (units[i]->isDead())
			delete units[i];
}

void Player::clearDeadUnits() {
	for (int i = 0; i < units.size(); i++)
		if (units[i]->isDead()) {
			delete units[i];
			units.erase(units.begin() + i);
		}
}

bool Player::hasWon(){
	return score >= maxScore;
}

int Player::getFaction() {
	return this->faction;
}

void Player::updateUnits() {
	for (int i = 0; i < units.size(); i++)
		units[i]->render();
	
}

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

void Player::addToScore() {
	if (score != maxScore)
		score += point;
}

int Player::getScore(){
	return score;
}

bool Player::isNext(Unit* unit, ControlPoint* cp) {
	int x = abs(cp->getX() - unit->getX())/ unit->getWidth();
	int y = abs(cp->getY() - unit->getY())/ unit->getHeight();
	if (x <= 1 && y <= 1)
		return true;
	return false;
}

void Player::addUnit(Unit * unit) {
	this->units.push_back(unit);
}

bool Player::containsUnit(Unit * unit) {
	for (int i = 0; i < units.size(); i++)
		if (units[i] == unit)
			return true;
	return false;
}

bool Player::noUnit() {
	return units.size() == 0;
}
