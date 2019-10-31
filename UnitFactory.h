
#ifndef UNITFACTORY_H
#define UNITFACTORY_H

#include "Unit.h"

class UnitFactory{

    public:
        static Unit *createUnit(int xPos, int yPos, int height, int width, int faction, int unitType, const std::string& imageFile, ImageHandler* imgHandler);

};

#endif
