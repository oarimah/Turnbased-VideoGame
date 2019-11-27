
#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"
#include "ControlPoint.h"
#include <vector>

class Player{

    private:
        std::vector<Unit*> units;
        std::vector<ControlPoint *>* cps;
        int numControlPoints;
        int faction;
        int point;
        int score;
        int maxScore;

    public:
        Player(int faction, int numCP, std::vector<ControlPoint *>* cp);
        ~Player();
        void clearDeadUnits();
        bool hasWon();
        void updateUnits();
        void reset();
        void addToScore();
        int getScore();
        bool isNext(Unit* unit, ControlPoint* cp);
        void addUnit(Unit* unit);
        bool containsUnit(Unit * unit);
        bool noUnit();
		int getFaction();

};

#endif // PLAYER_H
