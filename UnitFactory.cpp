#include "UnitFactory.h"

using namespace std;

Unit *UnitFactory::createUnit(int xPos, int yPos, int height, int width,
		int player, int faction, int unitType, ImageHandler* imgHandler) {\
	std::string colour;
	if (player == 1) 
		colour = "Red";
	else
		colour = "White";
	
		if (faction == 1) { // the british
			if (unitType == 0) { // swordsmen
				return new Unit(xPos, yPos, height, width,
						"Characters/" + colour + "General.png", imgHandler, 60, 14, 7, 3,
						1, 1, 3);
			} else if (unitType == 1) { // longbowmem
				return new Unit(xPos, yPos, height, width,
						"Characters/" + colour + "Bandit.png", imgHandler, 40, 20, 2, 2, 2,
						3, 3);
			} else if (unitType == 2) { // dragoon
				return new Unit(xPos, yPos, height, width,
						"Characters/" + colour + "Knight.png", imgHandler, 70, 17, 4, 2, 1,
						2, 4);
			}
		} else if (faction == 2) { // the french
			if (unitType == 0) { // men at arm
				return new Unit(xPos, yPos, height, width,
						"Characters/" + colour + "General.png", imgHandler, 75, 11, 8, 3,
						1, 1, 2);
			} else if (unitType == 1) { // crossbowmen
				return new Unit(xPos, yPos, height, width,
						"Characters/" + colour + "Bandit.png", imgHandler, 55, 16, 4, 2,
						1, 2, 3);
			} else if (unitType == 2) { // hussar
				return new Unit(xPos, yPos, height, width,
						"Characters/" + colour + "Knight.png", imgHandler, 55, 20, 5,
						2, 1, 1, 4);
			}
		} else if (faction == 3) { // the germans
                        if (unitType == 0) { // teutonic knight
                                return new Unit(xPos, yPos, height, width,
                                                "Characters/" + colour + "General.png", imgHandler, 120, 20, 5, 2,
                                                1, 1, 2);
                        } else if (unitType == 1) { // cuyler
                                return new Unit(xPos, yPos, height, width,
                                                "Characters/" + colour + "Bandit.png", imgHandler, 80, 14, 3, 3,
                                                2, 3, 2);
                        } else if (unitType == 2) { // turcopole
                                return new Unit(xPos, yPos, height, width,
                                                "Characters/" + colour + "Knight.png", imgHandler, 70, 10, 3,
                                                4, 2, 3, 3);
                        }
                } else if (faction == 4) { // the spanish
                        if (unitType == 0) { // conquistador
                                return new Unit(xPos, yPos, height, width,
                                                "Characters/" + colour + "General.png", imgHandler, 65, 12, 6, 3,
                                                2, 2, 4);
                        } else if (unitType == 1) { // arquebusier
                                return new Unit(xPos, yPos, height, width,
                                                "Characters/" + colour + "Bandit.png", imgHandler, 30, 23, 1, 2,
                                                2, 3, 4);
                        } else if (unitType == 2) { // jinete
                                return new Unit(xPos, yPos, height, width,
                                                "Characters/" + colour + "Knight.png", imgHandler, 60, 30, 3,
                                                2, 1, 1, 6);
                        }
                }


	return NULL;
}

