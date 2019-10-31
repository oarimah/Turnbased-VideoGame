
#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"
#include <vector>

class Player{

    private:
        std::vector<Unit*> units;
        int faction;

    public:
        Player(int faction);
        ~Player();
        int getFaction();
        void clearDeadUnits();
        void updateUnits();
        void addUnit(Unit* unit);
        bool containsUnit(Unit * unit);
        bool noUnit();

};

#endif // PLAYER_H
