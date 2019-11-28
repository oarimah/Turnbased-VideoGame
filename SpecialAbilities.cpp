/*! \class SpecialAbilities.cpp
 *  \class which gives the unit a temporary buff in stats based on the paremters passed
 *
 *  \gets the changes in stats and buffs the original stats of the unit for that duration of the time
 *  \uses arguments to get the changes in stats
 *  \author Osita Arimah
 *  \author Jake Nemiroff
 *  \author Abdallah Alasmar
 *  \param changeDefense get the change in defense for the unit
 *  \param changeOffense get the change in offense for the unit
 *  \param changeRangeStart get the change in the range start for the unit
 *  \param changeRangeEnds get the change in the range end for the unit
 *  \param changeNumAttacks get the change in the number of attacks for the unit
 *  \param changeInSpeed get the change in speed for the unit
 *  \param maxNumofTurns get the max number of turns for the specific unit
 *  \param maxCoolDownTurns get the cool down turns for the unit
 *  \return an Special Abilities object
 */
#include "SpecialAbilities.h"

/**
 * SpecialAbilities::SpecialAbilities(int changeDefense, int changeOffense, int changeRangeStart, int changeRangeEnds, int changeNumAttacks,int changeInSpeed, int maxNumofTurns, int maxCoolDownTurns)
 *
 * This is the constructor for a special Abilities Object
 *
 *
 * @param the changes of the stats of a unit, add/subtract to the unit's original stats
 * @return the special abilities object
 */
SpecialAbilities::SpecialAbilities(int changeDefense, int changeOffense, int changeRangeStart, int changeRangeEnds, int changeNumAttacks, int changeInSpeed, int maxNumofTurns, int maxCoolDownTurns)
{
    this->changeDefense = changeDefense;
    this->changeOffense = changeOffense;
    this->changeRangeStart = changeRangeStart;
    this->changeRangeEnds = changeRangeEnds;
    this->changeNumAttacks = changeNumAttacks;
    this->maxNumofTurns = maxNumofTurns;
    this->currNumofTurns = maxNumofTurns;
    this->maxCoolDownTurns = maxCoolDownTurns;
    this->currCoolDownTurns = 0;
    this->activated = false;
    this->changeInSpeed = changeInSpeed;
    this->statsReset = false; //reset checks if stats have been reset
}

/**
 * SpecialAbilities::~SpecialAbilities()
 *
 * This is the destructor for a special Abilities Object
 *
 *
 * @param none
 * @return destroy the object
 */
SpecialAbilities::~SpecialAbilities()
{
}

/**
 * int SpecialAbilities::getChangeInDefence()
 *
 * Get the change in the defense
 *
 *
 * @param none
 * @return the change in the defense
 */
int SpecialAbilities::getChangeInDefence()
{
    return this->changeDefense;
}

/**
 * int SpecialAbilities::getChangeInOffense()
 *
 * Get the change in the offense
 *
 *
 * @param none
 * @return the change in the offense
 */
int SpecialAbilities::getChangeInOffense()
{
    return this->changeOffense;
}

/**
 * int SpecialAbilities::getChangeInRangeStarts()
 *
 * Get the change in the range starts
 *
 *
 * @param none
 * @return the change in the range starts
 */
int SpecialAbilities::getChangeInRangeStarts()
{
    return this->changeRangeStart;
}

/**
 * int SpecialAbilities::getChangeInRangeEnds()
 *
 * Get the change in the range ends
 *
 *
 * @param none
 * @return the change in the range ends
 */
int SpecialAbilities::getChangeInRangeEnds()
{
    return this->changeRangeEnds;
}

/**
 * int SpecialAbilities::getChangeInNumAttacks()
 *
 * Get the change in the number of attacks
 *
 *
 * @param none
 * @return the change in the number of attacks
 */
int SpecialAbilities::getChangeInNumAttacks()
{
    return this->changeNumAttacks;
}

/**
 * int SpecialAbilities::getChangeInSpeed()
 *
 * Get the change in the speed
 *
 *
 * @param none
 * @return the change in the speed
 */
int SpecialAbilities::getChangeInSpeed()
{
    return this->changeInSpeed;
}

/**
 * void SpecialAbilities::activateAbility()
 *
 * set the activate bool to true
 *
 *
 * @param none
 * @return none
 */
void SpecialAbilities::activateAbility()
{
    this->activated = true;
}

/**
 * void SpecialAbilities::reset()
 *
 * handle the number of turns with the cool down turns
 *
 *
 * @param none
 * @return none
 */

void SpecialAbilities::reset()
{
    if (this->activated)
    {
        if (this->currNumofTurns != 0)
        {
            this->currNumofTurns--;

            if (this->currNumofTurns == 0)
            {
                this->currCoolDownTurns = this->maxCoolDownTurns;
                this->statsReset = true;
            }
        }
        else
        {
            this->statsReset = false;
            this->currCoolDownTurns--;
            if (this->currCoolDownTurns == 0)
            {
                this->currNumofTurns = this->maxNumofTurns;
                this->activated = false;
            }
        }
    }
}

/**
 * void SpecialAbilities::isActivated()
 *
 * check the activated bool
 *
 *
 * @param none
 * @return activated bool variable
 */
bool SpecialAbilities::isActivated()
{
    return this->activated;
}

/**
 * void SpecialAbilities::isStatsReset()
 *
 * check the resetStats bool variable
 *
 *
 * @param none
 * @return resetStats bool variable
 */

bool SpecialAbilities::isStatsReset()
{
    return this->statsReset;
}

/**
 * int SpecialAbilities::coolDownTurns()
 *
 * get the cooldown turns
 *
 *
 * @param none
 * @return return the cooldown turns of the unit
 */

int SpecialAbilities::coolDownTurns()
{
    return this->maxCoolDownTurns;
}

/**
 * int SpecialAbilities::effectTurns()
 *
 * get the max number of turns
 *
 *
 * @param none
 * @return return the number of turns
 */
int SpecialAbilities::effectTurns()
{
    return this->maxNumofTurns;
}
