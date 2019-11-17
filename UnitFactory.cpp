#include "UnitFactory.h"

using namespace std;

Unit *UnitFactory::createUnit(int xPos, int yPos, int height, int width,
		int player, int faction, int unitType, ImageHandler* imgHandler) {
	if (player == 1) {
		if (faction == 1) {
			if (unitType == 0) {
				return new Unit(xPos, yPos, height, width,
						"Characters/RedGeneral.png", imgHandler, 60, 14, 7, 3,
						1, 1, 3);
			} else if (unitType == 1) {
				return new Unit(xPos, yPos, height, width,
						"Characters/RedBandit.png", imgHandler, 40, 20, 2, 2, 2,
						3, 3);
			} else if (unitType == 2) {
				return new Unit(xPos, yPos, height, width,
						"Characters/RedKnight.png", imgHandler, 70, 17, 4, 2, 1,
						2, 4);
			}
		} else if (faction == 2) {
			if (unitType == 0) {
				return new Unit(xPos, yPos, height, width,
						"Characters/RedInfantry.png", imgHandler, 75, 11, 8, 3,
						1, 1, 2);
			} else if (unitType == 1) {
				return new Unit(xPos, yPos, height, width,
						"Characters/RedWrapman.png", imgHandler, 55, 16, 4, 2,
						1, 2, 3);
			} else if (unitType == 2) {
				return new Unit(xPos, yPos, height, width,
						"Characters/RedLightKnight.png", imgHandler, 55, 20, 5,
						2, 1, 1, 4);
			}
		}
	} else if (player == 2) {
		if (faction == 1) {
			if (unitType == 0) {
				return new Unit(xPos, yPos, height, width,
						"Characters/BlueGeneral.png", imgHandler, 60, 14, 7, 3,
						1, 1, 3);
			} else if (unitType == 1) {
				return new Unit(xPos, yPos, height, width,
						"Characters/BlueBandit.png", imgHandler, 40, 20, 2, 2,
						2, 3, 3);
			} else if (unitType == 2) {
				return new Unit(xPos, yPos, height, width,
						"Characters/BlueKnight.png", imgHandler, 70, 17, 4, 2,
						1, 2, 4);
			}
		} else if (faction == 2) {
			if (unitType == 0) {
				return new Unit(xPos, yPos, height, width,
						"Characters/BlueInfantry.png", imgHandler, 75, 11, 8, 3,
						1, 1, 2);
			} else if (unitType == 1) {
				return new Unit(xPos, yPos, height, width,
						"Characters/BlueWrapman.png", imgHandler, 55, 16, 4, 2,
						1, 2, 3);
			} else if (unitType == 2) {
				return new Unit(xPos, yPos, height, width,
						"Characters/BlueLightKnight.png", imgHandler, 55, 20, 5,
						2, 1, 1, 4);
			}
		}
	}
	return NULL;
}

