#include "SpecialAbilities.h"
using namespace std;

SpecialAbilities::SpecialAbilities(std::string changeDefense, std::string changeOffense, int changeRangeStart, int changeRangeEnds, int changeNumAttacks, int maxNumofTurns, int maxCoolDownTurns){
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
}
SpecialAbilities::~SpecialAbilities()
{
}
int SpecialAbilities::getChangeInDefence(){
    if (this->changeDefense.c_str()[this->changeDefense.length()-1] == 'p'){
        string c = this->changeDefense.substr(0,this->changeDefense.length());
        return (float)(atoi(c.c_str())/100)+1;
    } else
    {
        string c = this->changeDefense.substr(0,this->changeDefense.length());
        return (float)(atoi(c.c_str())/100)+1;
    }
}
int SpecialAbilities::getChangeInOffense(){
    if (this->changeOffense.c_str()[this->changeOffense.length()-1] == 'p'){
        string c = this->changeOffense.substr(0,this->changeDefense.length());
        return (float)(atoi(c.c_str())/100)+1;
    }
     else
    {
        string c = this->changeOffense.substr(0,this->changeOffense.length());
        return (float)(atoi(c.c_str())/100)+1;
    }
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
const bool SpecialAbilities::checkDefenseType(){
    if (this->changeDefense.c_str()[this->changeDefense.length()-1] == 'p'){
        return true;
    }else{
        return false;
     }
}
const bool SpecialAbilities::checkOffenseType(){
    if (this->changeOffense.c_str()[this->changeOffense.length()-1] == 'p'){
         return true;
     }else{
         return false;
     }
}
void SpecialAbilities::activateAbility(){
    activated= true;
}
void SpecialAbilities::resetAbility(){
    activated= false;
}

void SpecialAbilities::reset() {
    if (this->activated){
        if(this->currNumofTurns !=0){
            this->currNumofTurns--;
            if(this->currNumofTurns ==0)
                this->currCoolDownTurns = this->maxCoolDownTurns;
            
        } else {
            this->currCoolDownTurns--;
            if(this->currCoolDownTurns ==0)
                this->currNumofTurns = this->maxNumofTurns;
        }
    }
    activated=false;
}

void SpecialAbilities::coolDown(int n){
    if (activated == true){
        
    }
    
}