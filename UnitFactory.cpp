#include "UnitFactory.h"
using namespace std;

/*! \class UnitFactory
 *  \brief a class for making units
 *
 *  creates units based on the faction chosen and stores their stats in a Unit object
 *  uses if statements to check the faction before assigning unit stats
 *  \author Abdallah Alasmar
 *  \author Oluwadarasimi Ogunshote
 *  \author Osita Arimah
 *  \author Jake Nemiroff
 *  \param xPos the position of the unit on the horizontal axis
 *  \param yPos the position of the unit on the vertical axis
 *  \param height the height of the unit's model
 *  \param width the width of the unit's model
 *  \param player which player controls the unit
 *  \param faction which faction the unit belongs to
 *  \param unitType which of the three unit types (infantry, archers, light cavalry) the unit belongs to
 *  \param imgHandler handles the unit model
 *  \param sa contains the effects of the special ability of the unit
 *  \return an object of type Unit which has the stats of the unit that was created stored in it
 */
Unit * UnitFactory::createUnit(int xPos, int yPos, int height, int width, int player, int faction, int unitType, ImageHandler * imgHandler, SpecialAbilities* sa) {

    std::string colour;

    if (player == 1)
    colour = "Red";
    else
    colour = "White";

    if (faction == 1) { // the british
        if (unitType == 0) { // swordsmen
            return new Unit(xPos, yPos, height, width, "Characters/" + colour + "General.png", imgHandler, 60, 14, 7, 3, 1, 1, 3, new SpecialAbilities(-3, 7, 0, 0, 0, 0, 2, 5), "Swordsman");
        } else if (unitType == 1) { // longbowmen
             return new Unit(xPos, yPos, height, width, "Characters/" + colour + "Bandit.png", imgHandler, 40, 20, 2, 2, 2, 3, 3, new SpecialAbilities(0, 20, 0, 1, -1, 0, 2, 3), "Longbowman");
        } else if (unitType == 2) { // dragoon
            return new Unit(xPos, yPos, height, width,"Characters/" + colour + "Knight.png", imgHandler, 70, 17, 4, 2, 1, 2, 4, new SpecialAbilities(0, 0, 0, 0, 0, 3, 3, 1), "Dragoon");
        }
    }else if (faction == 2) { // the french
        if (unitType == 0) { // men at arm
            return new Unit(xPos, yPos, height, width, "Characters/" + colour + "General.png", imgHandler, 75, 11, 8, 3, 1, 1, 2, new SpecialAbilities(5, 0, 0, 0, 0, -2, 2, 3), "Man at Arms");
        } else if (unitType == 1) { // crossbowmen
            return new Unit(xPos, yPos, height, width,"Characters/" + colour + "Bandit.png", imgHandler, 55, 16, 4, 2, 1, 2, 3, new SpecialAbilities(3, -3, 0, 0, 2, 0, 2, 3), "Crossbowman");
        } else if (unitType == 2) { // hussar
            return new Unit(xPos, yPos, height, width, "Characters/" + colour + "Knight.png", imgHandler, 55, 20, 5, 2, 1, 1, 4, new SpecialAbilities(100, 15, 0, 0, -1, 0, 2, 6), "Hussar");
        }
    }else if (faction == 3) { // the germans
        if (unitType == 0) { // teutonic knight
            return new Unit(xPos, yPos, height, width,"Characters/" + colour + "General.png", imgHandler, 120, 20, 5, 2, 1, 1, 2, new SpecialAbilities(10, -8, 0, 0, 0, 0, 2, 2), "Teutonic Knight");
        } else if (unitType == 1) { // cuyler
            return new Unit(xPos, yPos, height, width,"Characters/" + colour + "Bandit.png", imgHandler, 80, 14, 3, 3, 2, 3, 2, new SpecialAbilities(2, 4, -1, -1, 0, 0, 2, 3), "Cuyler");
        }else if (unitType == 2) { // turcopole
            return new Unit(xPos, yPos, height, width,"Characters/" + colour + "Knight.png", imgHandler, 70, 10, 3, 4, 2, 3, 3, new SpecialAbilities(-3, 0, 0, 1, 1, 1, 3, 2), "Turcopole");
        }
    } else if (faction == 4) { // the spanish
        if (unitType == 0) { // conquistador
            return new Unit(xPos, yPos, height, width,"Characters/" + colour + "General.png", imgHandler, 65, 12, 6, 3, 1, 2, 4, new SpecialAbilities(-2, 0, 0, 0, 0, 2, 3, 1), "Conquistador");
        } else if (unitType == 1) { // arquebusier
            return new Unit(xPos, yPos, height, width,"Characters/" + colour + "Bandit.png", imgHandler, 30, 23, 1, 2, 2, 3, 4, new SpecialAbilities(100, 7, 0, 1, 1, 6, 1, 6), "Arquebusier");
        } else if (unitType == 2) { // jinete
            return new Unit(xPos, yPos, height, width,"Characters/" + colour + "Knight.png", imgHandler, 60, 30, 3, 2, 1, 1, 6, new SpecialAbilities(9, 0, 0, 0, 1, 3, 2, 2), "Jinete");
        }
    }


    return NULL;

}
