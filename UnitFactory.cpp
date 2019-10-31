
#include "UnitFactory.h"

using namespace std;

Unit *UnitFactory::createUnit(int xPos, int yPos, int height, int width, int faction, int unitType, ImageHandler* imgHandler) {
    if (faction == 1 && unitType == 0) {
        return new Unit(xPos, yPos, height, width, "Characters/ezgif.com-gif-maker(1).png", imgHandler, 60, 14, 7, 3, 1, 1, 3);
    } else if (faction == 1 && unitType == 1) {
        return new Unit(xPos, yPos, height, width, "Characters/ezgif.com-gif-maker(2).png", imgHandler, 40, 20, 2, 2, 2, 3, 3);
    } else if (faction == 1 && unitType == 2) {
        return new Unit(xPos, yPos, height, width, "Characters/ezgif.com-gif-maker(3).png", imgHandler, 70, 17, 4, 2, 1, 2, 4);
    } else if (faction == 2 && unitType == 0) {
        return new Unit(xPos, yPos, height, width, "Characters/ezgif.com-gif-maker.png", imgHandler, 75, 11, 8, 3, 1, 1, 2);
    } else if (faction == 2 && unitType == 1) {
        return new Unit(xPos, yPos, height, width, "Characters/ezgif.com-gif-maker(14).png", imgHandler, 55, 16, 4, 2, 1, 2, 3);
    } else if (faction == 2 && unitType == 2) {
        return new Unit(xPos, yPos, height, width, "Characters/ezgif.com-gif-maker(15).png", imgHandler, 55, 20, 5, 2, 1, 1, 4);
    } else {
        return NULL;
    }
}

