#ifndef UNIT_FACTORY_H
#define UNIT_FACTORY_H

#include "Unit.h"
#include "SpecialAbilities.h"

class UnitFactory {

public:
    static Unit *createUnit(int xPos, int yPos, int height, int width,
                            int player, int faction, int unitType, ImageHandler* imgHandler,SpecialAbilities* sa);


};

#endif

