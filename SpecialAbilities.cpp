#include "SpecialAbilities.h"

SpecialAbilities::SpecialAbilities(int changeDefense, int changeOffense, int changeRangeStart, int changeRangeEnds, int changeNumAttacks,int changeInSpeed, int maxNumofTurns, int maxCoolDownTurns){


    this->changeDefense = changeDefense;
    this->changeOffense = changeOffense;
    this->changeRangeStart= changeRangeStart;
    this->changeRangeEnds=changeRangeEnds;
    this->changeNumAttacks= changeNumAttacks;
    this->maxNumofTurns = maxNumofTurns;
    this->currNumofTurns = maxNumofTurns;
    this->maxCoolDownTurns= maxCoolDownTurns;
    this->currCoolDownTurns = 0;
    this->activated = false;
    this->changeInSpeed = changeInSpeed;
    this->statsReset=true;//reset checks if stats have been reset

}

SpecialAbilities::~SpecialAbilities()
{
}

int SpecialAbilities::getChangeInDefence(){
    return this->changeDefense;
}

int SpecialAbilities::getChangeInOffense(){
    return this->changeOffense;
}
int SpecialAbilities::getChangeInRangeStarts(){
    return this->changeRangeStart;
}
int SpecialAbilities::getChangeInRangeEnds(){
    return this->changeRangeEnds;
}
int SpecialAbilities::getChangeInNumAttacks(){
    return this->changeNumAttacks;
}
int SpecialAbilities::getChangeInSpeed(){
    return this->changeInSpeed;
}

void SpecialAbilities::activateAbility(){
    this->activated= true;
}

void SpecialAbilities::resetAbility(){
    this->activated= false;
}


void SpecialAbilities::reset(){
    if (this->activated) {
        this->statsReset = false;
        if (this->currNumofTurns != 0) {
            this->currNumofTurns--;
            if (this->currNumofTurns == 0)
                this->currCoolDownTurns = this->maxCoolDownTurns;
        } else {
            this->currCoolDownTurns--;
            if (this->currCoolDownTurns == 0) {
                this->currNumofTurns = this->maxNumofTurns;
                this->activated = false;
               // this->statsReset=true;
            }
        }
    }this->statsReset=true;
}


bool SpecialAbilities::isActivated() {
    return this->activated;
}

bool SpecialAbilities::isReset(){
    //return this->reset;
}

int SpecialAbilities::coolDownTurns(){
	return this->maxCoolDownTurns;
}

int SpecialAbilities::effectTurns(){

    this->statsReset=true;
	return this->maxNumofTurns;
}

void SpecialAbilities::resetStats(){
    this->statsReset=true;
}

bool SpecialAbilities::isStatsReset(){
	return this->statsReset;
}
