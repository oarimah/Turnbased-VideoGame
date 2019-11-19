#include "Player.h"

using namespace std;

Player::Player(int faction) {
	this->faction = faction;
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
