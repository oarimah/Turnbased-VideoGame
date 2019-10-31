
#include "Player.h"

using namespace std;

Player::Player(int faction) {
    this->faction = faction;
}

void Player::clearDeadUnits() {
    for (int i = 0 ; i < units.size(); i++)
        if(units[i]->isDead()) {
            delete units[i];
            units.erase(i);
        }
}

void Player::updateUnits() {
    for (int i = 0 ; i < units.size(); i++)
        units[i]->render();
}

void Player::addUnit(Unit unit) {
    units.push_back(unit);
    unit.setPlayer(this);
}

bool Player::noUnit() {
    return units.size() == 0;
}
